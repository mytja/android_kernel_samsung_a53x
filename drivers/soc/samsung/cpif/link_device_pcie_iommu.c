// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 Samsung Electronics.
 *
 */

#include <soc/samsung/exynos-pcie-iommu-exp.h>
#include "link_device_pcie_iommu.h"

void cpif_pcie_iommu_enable_regions(struct mem_link_device *mld)
{
	static bool enabled_region;

	struct pktproc_adaptor *ppa = &mld->pktproc;
	struct link_device *ld = &mld->link_dev;
	struct modem_ctl *mc = ld->mc;

	u32 cp_num = ld->mdm_data->cp_num;
	u32 shmem_idx;
	u32 size;
	int ret;

	if (enabled_region)
		return;

	for (shmem_idx = 0 ; shmem_idx < MAX_CP_SHMEM ; shmem_idx++) {
		if (shmem_idx == SHMEM_MSI && !(mld->attrs & LINK_ATTR_XMIT_BTDLR_PCIE))
			continue;

		if (shmem_idx == SHMEM_PKTPROC)
			size = ppa->buff_rgn_offset;
		else
			size = cp_shmem_get_size(cp_num, shmem_idx);

		if (cp_shmem_get_base(cp_num, shmem_idx)) {
			ret = pcie_iommu_map(cp_shmem_get_base(cp_num, shmem_idx),
					     cp_shmem_get_base(cp_num, shmem_idx),
					     size, 0, mc->pcie_ch_num);
			mif_info("pcie iommu idx:%d addr:0x%08lx size:0x%08x ret:%d\n",
				 shmem_idx, cp_shmem_get_base(cp_num, shmem_idx), size, ret);
		}
	}

	enabled_region = true;
}

int cpif_pcie_iommu_init(struct pktproc_queue *q)
{
	struct cpif_pcie_iommu_ctrl *ioc = &q->ioc;
	size_t size = sizeof(void *) * q->num_desc;

	mif_info("iommu init num_desc:%u\n", q->num_desc);

	if (ioc->pf_buf) {
		memset(ioc->pf_buf, 0, size);
	} else {
		ioc->pf_buf = kvzalloc(size, GFP_KERNEL);
		if (!ioc->pf_buf)
			return -ENOMEM;
	}

	return 0;
}

void cpif_pcie_iommu_reset(struct pktproc_queue *q)
{
	struct pktproc_desc_sktbuf *desc = q->desc_sktbuf;
	struct cpif_pcie_iommu_ctrl *ioc = &q->ioc;
	unsigned int usage, idx;
	bool do_unmap = true;

	if (!ioc->pf_buf)
		return;

	usage = circ_get_usage(q->num_desc, ioc->curr_fore, q->done_ptr);
	idx = q->done_ptr;

	mif_info("iommu reset done:%u curr_fore:%u usage:%u, fore:%u\n",
		 q->done_ptr, ioc->curr_fore, usage, *q->fore_ptr);

	while (usage--) {
		if (do_unmap) {
			unsigned long src_pa;

			src_pa = desc[idx].cp_data_paddr - q->cp_buff_pbase +
				 q->q_buff_pbase - q->ppa->skb_padding_size;
			cpif_pcie_iommu_try_ummap_va(q, src_pa, ioc->pf_buf[idx], idx);

			/* Just free the frags if not mapped yet */
			if (idx == *q->fore_ptr)
				do_unmap = false;
		}

		page_frag_free(ioc->pf_buf[idx]);
		idx = circ_new_ptr(q->num_desc, idx, 1);
	}

	/* Initialize */
	if (ioc->pf_cache.va) {
		__page_frag_cache_drain(virt_to_page(ioc->pf_cache.va),
					ioc->pf_cache.pagecnt_bias);
	}
	memset(&q->ioc, 0, offsetof(struct cpif_pcie_iommu_ctrl, pf_buf));
}

void *cpif_pcie_iommu_map_va(struct pktproc_queue *q, unsigned long src_pa,
			     u32 idx, u32 *map_cnt)
{
	struct modem_ctl *mc = dev_get_drvdata(q->ppa->dev);
	struct cpif_pcie_iommu_ctrl *ioc = &q->ioc;
	const size_t pf_size = q->ppa->true_packet_size;
	void *addr_des, *addr_asc;

	/*
	 * Every page orders are compatible with IOMMU granularity.
	 * But the poped addrs are in descending order.
	 */
	addr_des = page_frag_alloc(&ioc->pf_cache, pf_size, GFP_ATOMIC);
	if (!addr_des) {
		mif_err_limited("failed to alloc page frag\n");
		return NULL;
	}

	/* Map the last page */
	*map_cnt = 0;
	if (ioc->map_page_va != ioc->pf_cache.va) {
		unsigned long map_size;
		int ret;

		if (!ioc->map_src_pa)
			goto set_map;

		map_size = page_size(virt_to_page(ioc->map_page_va));

		mif_debug("map idx:%u src_pa:0x%lX va:0x%p size:0x%lX\n",
			  ioc->map_idx, ioc->map_src_pa, ioc->map_page_va, map_size);

		ret = pcie_iommu_map(ioc->map_src_pa, virt_to_phys(ioc->map_page_va),
				     map_size, 0, mc->pcie_ch_num);
		if (ret) {
			mif_err("map failure idx:%u src_pa:0x%lX va:0x%p size:0x%lX\n",
				ioc->map_idx, ioc->map_src_pa, ioc->map_page_va, map_size);
			return NULL;
		}
		ioc->mapped_cnt++;
		ioc->mapped_size += map_size;

		/* Store the last mapping size */
		if (!idx)
			ioc->end_map_size = (u32)map_size;

		*map_cnt = circ_get_usage(q->num_desc, idx, ioc->map_idx);

set_map:
		ioc->map_src_pa = src_pa;
		ioc->map_page_va = ioc->pf_cache.va;
		ioc->map_idx = idx;
		ioc->pf_offset = 0;
	}

	/* Convert an address in accending order */
	addr_asc = ioc->pf_cache.va + ioc->pf_offset;

	ioc->pf_buf[idx] = addr_asc;
	ioc->pf_offset += pf_size;
	ioc->curr_fore = idx;

	/*
	 * The first buffer should be mapped with a new page.
	 * Drain the page frag cache at the last buffer.
	 */
	if (idx == (q->num_desc - 1)) {
		__page_frag_cache_drain(virt_to_page(ioc->pf_cache.va),
					ioc->pf_cache.pagecnt_bias);
		ioc->pf_cache.va = NULL;
	}

	return addr_asc;
}

void cpif_pcie_iommu_try_ummap_va(struct pktproc_queue *q, unsigned long src_pa,
				  void *addr, u32 idx)
{
	struct modem_ctl *mc = dev_get_drvdata(q->ppa->dev);
	struct cpif_pcie_iommu_ctrl *ioc = &q->ioc;
	struct page *p = virt_to_head_page(addr);
	u32 unmap_size;
	size_t ret;

	if (ioc->unmap_page == p)
		return;

	if (!ioc->unmap_src_pa)
		goto set_unmap;

	/*
	 * Cannot not ensure that ioc->unmap_page has a valid page addr.
	 * Use the variable to keep an addr only.
	 */

	if (!idx)
		unmap_size = ioc->end_map_size;
	else
		unmap_size = (u32)(src_pa - ioc->unmap_src_pa);

	mif_debug("unmap src_pa:0x%lX size:0x%X\n", ioc->unmap_src_pa, unmap_size);

	ret = pcie_iommu_unmap(ioc->unmap_src_pa, unmap_size, mc->pcie_ch_num);
	if (ret != unmap_size) {
		mif_err("invalid unmap size:0x%zX expected:0x%X src_pa:0x%lX\n",
			ret, unmap_size, ioc->unmap_src_pa);
	}
	ioc->mapped_cnt--;
	ioc->mapped_size -= unmap_size;

set_unmap:
	ioc->unmap_src_pa = src_pa;
	ioc->unmap_page = p;
}
