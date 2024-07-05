#ifndef _NPU_MEMORY_H_
#define _NPU_MEMORY_H_

#include <linux/platform_device.h>
#include <media/videobuf2-core.h>
#if defined(CONFIG_VIDEOBUF2_CMA_PHYS)
#include <media/videobuf2-cma-phys.h>
#elif defined(CONFIG_VIDEOBUF2_ION)
#include <media/videobuf2-ion.h>
#endif

#define MODERN_ION

struct npu_memory_buffer {
	struct list_head		list;
#ifdef CONFIG_DSP_USE_VS4L
	struct list_head		dsp_list;
#endif
	struct dma_buf			*dma_buf;
	struct dma_buf_attachment	*attachment;
	struct sg_table			*sgt;
	dma_addr_t			daddr;
	phys_addr_t			paddr;
	void				*vaddr;
	size_t				size;
	size_t				used_size;
#ifdef CONFIG_NPU_USE_IMB_ALLOCATOR
	size_t				ncp_max_size;
#endif
	int				fd;
	char name[15];
};

struct npu_memory_v_buf {
	struct list_head		list;
	u8				*v_buf;
	size_t				size;
	char name[15];
};

struct npu_memory;
struct npu_mem_ops {
	int (*resume)(struct npu_memory *memory);
	int (*suspend)(struct npu_memory *memory);
};

struct npu_memory {
	struct device			*dev;
	struct ion_client		*client;
	const struct npu_mem_ops	*npu_mem_ops;
	const struct vb2_mem_ops	*vb2_mem_ops;
	atomic_t			refcount;

	spinlock_t			map_lock;
	struct list_head		map_list;
	u32				map_count;

	spinlock_t			alloc_lock;
	struct list_head		alloc_list;
	u32				alloc_count;

	spinlock_t			valloc_lock;
	struct list_head		valloc_list;
	u32				valloc_count;
};

int npu_memory_probe(struct npu_memory *memory, struct device *dev);
int npu_memory_open(struct npu_memory *memory);
int npu_memory_close(struct npu_memory *memory);
int npu_memory_map(struct npu_memory *memory, struct npu_memory_buffer *buffer, int prot);
void npu_memory_unmap(struct npu_memory *memory, struct npu_memory_buffer *buffer);
struct npu_memory_buffer *npu_memory_copy(struct npu_memory *memory,
					struct npu_memory_buffer *buffer, size_t offset, size_t size);
int npu_memory_alloc(struct npu_memory *memory, struct npu_memory_buffer *buffer, int prot);
int npu_memory_alloc_cached(struct npu_memory *memory, struct npu_memory_buffer *buffer, int prot);
int npu_memory_alloc_secure(struct npu_memory *memory, struct npu_memory_buffer *buffer, int prot);
int npu_memory_free(struct npu_memory *memory, struct npu_memory_buffer *buffer);
int npu_memory_v_alloc(struct npu_memory *memory, struct npu_memory_v_buf *buffer);
void npu_memory_v_free(struct npu_memory *memory, struct npu_memory_v_buf *buffer);
int npu_memory_secure_alloc(struct npu_memory *memory, struct npu_memory_buffer *buffer, int prot);
int npu_memory_secure_free(struct npu_memory *memory, struct npu_memory_buffer *buffer);
void npu_memory_dump(struct npu_memory *memory);

#endif
