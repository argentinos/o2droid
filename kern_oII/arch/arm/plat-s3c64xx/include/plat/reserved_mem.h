#ifndef _ASM_ARM_ARCH_RESERVED_MEM_H
#define _ASM_ARM_ARCH_RESERVED_MEM_H

#include <linux/types.h>
#include <linux/list.h>
#include <asm/setup.h>

#define DRAM_END_ADDR 				(UL(0x66000000))//?65

#define RESERVED_PMEM_END_ADDR 		(DRAM_END_ADDR)



#define RESERVED_MEM_CMM		(3 * 1024 * 1024)
#define RESERVED_MEM_MFC		(6 * 1024 * 1024)
#define RESERVED_PMEM_PICTURE		(6 * 1024 * 1024)	/* PMEM_PIC and MFC use share area */
#define RESERVED_PMEM_JPEG		(3 * 1024 * 1024)
#define RESERVED_PMEM_PREVIEW		(2 * 1024 * 1024) //2
#define RESERVED_PMEM_RENDER	  	(4 * 1024 * 1024) //2 too small
#define RESERVED_PMEM_STREAM	  	(2 * 1024 * 1024) //4 problems: 8
#define RESERVED_G3D			(32 * 1024 * 1024) 	/* G3D is shared with uppper memory areas */
#define RESERVED_PMEM_GPU1		(0) //0
#define RESERVED_PMEM			(12 * 1024 * 1024)
#define RESERVED_PMEM_SKIA		(0)//0

#define RESERVED_G3D_UI			(6 * 1024 * 1024)
#define RESERVED_G3D_SHARED		(RESERVED_MEM_CMM + RESERVED_MEM_MFC + RESERVED_PMEM_STREAM + RESERVED_PMEM_JPEG + RESERVED_PMEM_PREVIEW + RESERVED_PMEM_RENDER)
#define RESERVED_G3D_APP		(RESERVED_G3D - RESERVED_G3D_UI - RESERVED_G3D_SHARED)

//#if defined(CONFIG_RESERVED_MEM_CMM_JPEG_MFC_POST_CAMERA)
#define CMM_RESERVED_MEM_START		(RESERVED_PMEM_END_ADDR - RESERVED_MEM_CMM) //-3m
#define MFC_RESERVED_MEM_START		(CMM_RESERVED_MEM_START - RESERVED_MEM_MFC) //-6m
#define PICTURE_RESERVED_PMEM_START	(MFC_RESERVED_MEM_START) //0m
#define JPEG_RESERVED_PMEM_START	(MFC_RESERVED_MEM_START - RESERVED_PMEM_JPEG) //-3m
#define PREVIEW_RESERVED_PMEM_START	(JPEG_RESERVED_PMEM_START - RESERVED_PMEM_PREVIEW) //2m
#define RENDER_RESERVED_PMEM_START	(PREVIEW_RESERVED_PMEM_START - RESERVED_PMEM_RENDER) //-2m
#define STREAM_RESERVED_PMEM_START	(RENDER_RESERVED_PMEM_START - RESERVED_PMEM_STREAM) //-4m
#define G3D_RESERVED_START		(RESERVED_PMEM_END_ADDR - RESERVED_G3D)		 // G3D is shared //-32m
#define GPU1_RESERVED_PMEM_START	(G3D_RESERVED_START - RESERVED_PMEM_GPU1) //0m
#define RESERVED_PMEM_START		(GPU1_RESERVED_PMEM_START - RESERVED_PMEM) //8m
#define PHYS_UNRESERVED_SIZE		(RESERVED_PMEM_START - UL(0x60000000))

#define SKIA_RESERVED_PMEM_START	(0)


struct s3c6410_pmem_setting{
        resource_size_t pmem_start;
        resource_size_t pmem_size;
        resource_size_t pmem_gpu1_start;
        resource_size_t pmem_gpu1_size;
        resource_size_t pmem_render_start;
        resource_size_t pmem_render_size;
        resource_size_t pmem_render_pic_start;
        resource_size_t pmem_render_pic_size;
        resource_size_t pmem_stream_start;
        resource_size_t pmem_stream_size;
        resource_size_t pmem_preview_start;
        resource_size_t pmem_preview_size;
        resource_size_t pmem_picture_start;
        resource_size_t pmem_picture_size;
        resource_size_t pmem_jpeg_start;
        resource_size_t pmem_jpeg_size;
        resource_size_t pmem_skia_start;
        resource_size_t pmem_skia_size;
};
 
void s3c6410_add_mem_devices (struct s3c6410_pmem_setting *setting);

#endif /* _ASM_ARM_ARCH_RESERVED_MEM_H */
