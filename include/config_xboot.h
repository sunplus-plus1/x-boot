#ifndef _INC_CONFIG_XBOOT_
#define _INC_CONFIG_XBOOT_

#include <config.h>

////////////////////////////////////////////////////////////////////////////
//
// Config (xboot)
//

//
// Image Address (source)
//

// SPI NOR
#if defined(PLATFORM_Q645) || defined(PLATFORM_SP7350)
#define SPI_DTB_OFFSET        0x048000   // 288K
#define SPI_UBOOT_OFFSET      0x068000   // 416K
#define SPI_FIP_OFFSET        0x128000   // 1M+160K
#define SPI_LINUX_OFFSET      0x200000   // 2M
#else
#define SPI_DTB_OFFSET        0x020000   // 128K
#define SPI_UBOOT_OFFSET      0x040000   // 256K
#define SPI_INITRAMFS_OFFSET  0x400000   // 4M
#define SPI_LINUX_OFFSET      0x600000   // 6M
#endif

//
// Load & Run Address
//

// draminit
#define DRAMINIT_LOAD_ADDR   (g_io_buf.usb.draminit_tmp)  /* 9e804d00 */
#define DRAMINIT_RUN_ADDR    (DRAMINIT_LOAD_ADDR + 0x40)  /* skip header */

// dram_test
#ifdef PLATFORM_I143
#define DRAM_TEST_BEGIN      0xA0800000
#else
#define DRAM_TEST_BEGIN      0x800000
#endif
#define DRAM_TEST_LEN        1024
#define DRAM_TEST_END        (DRAM_TEST_BEGIN + DRAM_TEST_LEN)

#if defined(PLATFORM_Q645) || defined(PLATFORM_SP7350)
// u-boot
#define UBOOT_LOAD_ADDR         0x500000
#define UBOOT_RUN_ADDR          (UBOOT_LOAD_ADDR + 0x40)
#define UBOOT_MAX_LEN           0x100000

#define BL31_RUN_ADDR           0x200000
#define OPTEE_RUN_ADDR          0x300000
#define FIP_MAX_LEN             0x200000
#define FIP_LOAD_ADDR           0x1000000

#define SMP_CORES 4

// DTB
#define DTB_RUN_ADDR            0x1F80000                   /* skip header */
#define DTB_LOAD_ADDR           (DTB_RUN_ADDR - 0x40)       /* dtb */

// Linux
#define LINUX_RUN_ADDR          0x2000000                   /* vmlinux */
#define LINUX_LOAD_ADDR         (LINUX_RUN_ADDR - 0x40)     /* - header */

// initramfs
#define INITRAMFS_RUN_ADDR      0x2100000                   /* cpio */
#define INITRAMFS_LOAD_ADDR     (INITRAMFS_RUN_ADDR - 0x40)

//mmu pagetable
#define MMU_PGTBL_ADDR 		0x000FC000   /*(1M-16k)*/

#define CM4_BOOT_ADDR		0x77000000

#elif defined(PLATFORM_I143)
#define OPENSBI_RUN_ADDR        0xA01D0000

// freertos
#define FREERTOS_RUN_ADDR       0xA0000040
#define FREERTOS_LOAD_ADDR      0xA0000000

// u-boot
#define UBOOT_RUN_ADDR_A_VIEW   0x20100000
#define UBOOT_RUN_ADDR          0xA0100040
#define UBOOT_LOAD_ADDR         0xA0100000
#define UBOOT_MAX_LEN           0x400000

// DTB
#define DTB_RUN_ADDR_A_VIEW     0x201F0000                      /* for  C+P */
#define DTB_RUN_ADDR            0xA01F0000                      /* dtb */
#define DTB_LOAD_ADDR           (DTB_RUN_ADDR-0X40)             /* skip header */
#define DTB_MAX_LEN             0x8000

// Linux
#define LINUX_RUN_ADDR_A_VIEW   0x20028000                      /* for  C+P */
#define LINUX_RUN_ADDR          0xA0200000                      /* vmlinux */
#define LINUX_LOAD_ADDR         (LINUX_RUN_ADDR - 0x40)         /* - header */

// initramfs
#define INITRAMFS_RUN_ADDR      0xA2000000                      /* cpio */
#define INITRAMFS_LOAD_ADDR     (INITRAMFS_RUN_ADDR - 0x40)

#else
// u-boot
#define UBOOT_LOAD_ADDR      0x200000
#define UBOOT_RUN_ADDR       0x200040
#define UBOOT_MAX_LEN        0x200000

// DTB
#define DTB_LOAD_ADDR        (0x300000 - 0x40)          /* dtb */
#define DTB_RUN_ADDR         0x300000                   /* skip header */

// Linux
#define LINUX_RUN_ADDR       0x308000                   /* vmlinux */
#define LINUX_LOAD_ADDR      (LINUX_RUN_ADDR - 0x40)    /* - header */

// initramfs
#define INITRAMFS_RUN_ADDR   0x2100000                   /* cpio */
#define INITRAMFS_LOAD_ADDR  (INITRAMFS_RUN_ADDR - 0x40)

#endif


// need to load initramfs if it's split from uImage
//#define LOAD_SPLIT_INITRAMFS

/////////////////////////
// mkimage Type
// mkimage -T standalone --> uhdr with CRC32
// mkimage -T quickboot  --> uhdr with SUM32

#define USE_QKBOOT_IMG  // consistent with draminit and uboot image

/* ISP image offset */
#define ISP_IMG_OFF_XBOOT    (0)
#if defined(PLATFORM_Q645) || defined(PLATFORM_SP7350)
#define ISP_IMG_OFF_UBOOT    (192 * 1024)
#define ISP_IMG_OFF_HEADER   (1*1024*1024)
#else
#define ISP_IMG_OFF_UBOOT    (64 * 1024)
#endif

//
// ABIO config
//
#define ABIO_32M   0x200408
#define ABIO_100M  0x080718
#define ABIO_200M  0x040718
#define ABIO_400M  0x020718

#define ABIO_IOCTRL_CFG     0x00f1e004 //for cpio timing (xhdu)  /* asic A_G0.18 io delay (xhdu, POSTSIM_ON) */

#ifdef CONFIG_PLATFORM_I137
#define ABIO_CFG ABIO_200M
#else
#define ABIO_CFG ABIO_400M
//#define A_PLL_CTL0_CFG      0x2c5109  /* default: pllclk=1215M, corelck= 607.5M */
#define A_PLL_CTL0_CFG      0x445149    /* pllclk=1863M, corelck= 931.5M */
#endif

#endif

