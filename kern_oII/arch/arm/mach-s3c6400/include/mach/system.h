/* linux/arch/arm/mach-s3c6400/include/mach/system.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C6400 - system implementation
 */

#ifndef __ASM_ARCH_SYSTEM_H
#define __ASM_ARCH_SYSTEM_H __FILE__

#include <linux/io.h>
#include <mach/map.h>
#include <plat/regs-watchdog.h>

void (*s3c64xx_idle)(void);
void (*s3c64xx_reset_hook)(void);

//#ifdef CONFIG_MACH_SATURN
#if 1 //bss
extern void __iomem *s3c6410_wdt_addr;
#endif

void s3c64xx_default_idle(void)
{
	/* nothing here yet */
}
	
static void arch_idle(void)
{
	if (s3c64xx_idle != NULL)
		(s3c64xx_idle)();
	else
		s3c64xx_default_idle();
}

void arch_reset(char mode)
{
//#ifdef CONFIG_MACH_SATURN
#if 1 //bss
	void __iomem	*wdt_reg = s3c6410_wdt_addr;

	printk(KERN_ERR ">>Watchdog reset tried to assert reset\n");
	mdelay(50);

	if (!wdt_reg ){
		//wdt_reg = ioremap(S3C64XX_PA_WATCHDOG,S3C64XX_SZ_WATCHDOG);
		while(1);
		}
#else
	void __iomem	*wdt_reg;

	printk(KERN_ERR ">>Watchdog reset tried to assert reset\n");
	wdt_reg = ioremap(S3C64XX_PA_WATCHDOG,S3C64XX_SZ_WATCHDOG);
#endif

	/* nothing here yet */

	writel(S3C_WTCNT_CNT, wdt_reg + S3C_WTCNT_OFFSET);	/* Watchdog Count Register*/
	writel(S3C_WTCNT_CON, wdt_reg + S3C_WTCON_OFFSET);	/* Watchdog Controller Register*/
	writel(S3C_WTCNT_DAT, wdt_reg + S3C_WTDAT_OFFSET);	/* Watchdog Data Register*/

	/* wait for reset to assert... */
	mdelay(500);

	printk(KERN_ERR "<<Watchdog reset failed to assert reset\n");

	/* delay to allow the serial port to show the message */
	mdelay(50);
}

#endif /* __ASM_ARCH_IRQ_H */
