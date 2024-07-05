// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF Heap Allocator - secure management
 *
 * Copyright (c) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */

#include <linux/slab.h>
#include <linux/genalloc.h>
#include <linux/smc.h>
#include <linux/kmemleak.h>
#include <linux/dma-mapping.h>
#include <linux/dma-direct.h>
#include <linux/samsung-secure-iova.h>

#include "secure_buffer.h"
#include "heap_private.h"

static int buffer_protect_smc(struct device *dev, struct buffer_prot_info *protdesc,
			      unsigned int protalign)
{
	unsigned long size = protdesc->chunk_count * protdesc->chunk_size;
	unsigned long ret, dma_addr = 0;

	dma_addr = secure_iova_alloc(size, max_t(u32, protalign, PAGE_SIZE));
	if (!dma_addr)
		return -ENOMEM;

	protdesc->dma_addr = (unsigned int)dma_addr;

	dma_map_single(dev, protdesc, sizeof(*protdesc), DMA_TO_DEVICE);

	ret = ppmp_smc(SMC_DRM_PPMP_PROT, virt_to_phys(protdesc), 0, 0);
	if (ret) {
		dma_unmap_single(dev, phys_to_dma(dev, virt_to_phys(protdesc)), sizeof(*protdesc),
				 DMA_TO_DEVICE);
		secure_iova_free(dma_addr, size);
		perr("CMD %#x (err=%#lx,dva=%#x,size=%#lx,cnt=%u,flg=%u,phy=%#lx)",
		     SMC_DRM_PPMP_UNPROT, ret, protdesc->dma_addr,
		     protdesc->chunk_size, protdesc->chunk_count,
		     protdesc->flags, protdesc->bus_address);
		return -EACCES;
	}

	return 0;
}

static int buffer_unprotect_smc(struct device *dev,
				struct buffer_prot_info *protdesc)
{
	unsigned long size = protdesc->chunk_count * protdesc->chunk_size;
	unsigned long ret;

	dma_unmap_single(dev, phys_to_dma(dev, virt_to_phys(protdesc)), sizeof(*protdesc),
			 DMA_TO_DEVICE);

	ret = ppmp_smc(SMC_DRM_PPMP_UNPROT, virt_to_phys(protdesc), 0, 0);
	if (ret) {
		perr("CMD %#x (err=%#lx,dva=%#x,size=%#lx,cnt=%u,flg=%u,phy=%#lx)",
		     SMC_DRM_PPMP_UNPROT, ret, protdesc->dma_addr,
		     protdesc->chunk_size, protdesc->chunk_count,
		     protdesc->flags, protdesc->bus_address);
		return -EACCES;
	}
	/*
	 * retain the secure device address if unprotection to its area fails.
	 * It might be unusable forever since we do not know the state of the
	 * secure world before returning error from ppmp_smc() above.
	 */
	secure_iova_free(protdesc->dma_addr, size);

	return 0;
}

void *samsung_dma_buffer_protect(struct samsung_dma_heap *heap, unsigned int chunk_size,
				 unsigned int nr_pages, unsigned long paddr)
{
	struct device *dev = dma_heap_get_dev(heap->dma_heap);
	struct buffer_prot_info *protdesc;
	unsigned int protalign = heap->alignment;
	unsigned int array_size = 0;
	int ret;

	protdesc = kmalloc(sizeof(*protdesc), GFP_KERNEL);
	if (!protdesc)
		return ERR_PTR(-ENOMEM);

	protdesc->chunk_count = nr_pages;
	protdesc->flags = heap->protection_id;
	protdesc->chunk_size = ALIGN(chunk_size, protalign);
	protdesc->bus_address = paddr;

	if (protdesc->chunk_count > 1) {
		void *vaddr = phys_to_virt(paddr);

		array_size = sizeof(paddr) * nr_pages;

		kmemleak_ignore(vaddr);
		dma_map_single(dev, vaddr, array_size, DMA_TO_DEVICE);
	}

	ret = buffer_protect_smc(dev, protdesc, protalign);
	if (ret) {
		if (protdesc->chunk_count > 1)
			dma_unmap_single(dev, phys_to_dma(dev, paddr), array_size, DMA_TO_DEVICE);

		kfree(protdesc);
		return ERR_PTR(ret);
	}

	return protdesc;
}

int samsung_dma_buffer_unprotect(void *priv, struct device *dev)
{
	struct buffer_prot_info *protdesc = priv;
	int ret = 0;

	if (!priv)
		return 0;

	if (protdesc->chunk_count > 1)
		dma_unmap_single(dev, phys_to_dma(dev, protdesc->bus_address),
				 sizeof(unsigned long) * protdesc->chunk_count, DMA_TO_DEVICE);

	ret = buffer_unprotect_smc(dev, protdesc);
	kfree(protdesc);

	return ret;
}
