/* linux/arch/arm/plat-s3c/include/plat/gpio-cfg.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Platform - GPIO pin configuration
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

/* This file contains the necessary definitions to get the basic gpio
 * pin configuration done such as setting a pin to input or output or
 * changing the pull-{up,down} configurations.
 */

/* Note, this interface is being added to the s3c64xx arch first and will
 * be added to the s3c24xx systems later.
 */

#ifndef __PLAT_GPIO_CFG_H
#define __PLAT_GPIO_CFG_H __FILE__

typedef unsigned int __bitwise__ s3c_gpio_pull_t;

/* forward declaration if gpio-core.h hasn't been included */
struct s3c_gpio_chip;

/**
 * struct s3c_gpio_cfg GPIO configuration
 * @cfg_eint: Configuration setting when used for external interrupt source
 * @get_pull: Read the current pull configuration for the GPIO
 * @set_pull: Set the current pull configuraiton for the GPIO
 * @set_pin: Set the current output level for the GPIO
 * @set_config: Set the current configuration for the GPIO
 * @get_config: Read the current configuration for the GPIO
 *
 * Each chip can have more than one type of GPIO bank available and some
 * have different capabilites even when they have the same control register
 * layouts. Provide an point to vector control routine and provide any
 * per-bank configuration information that other systems such as the
 * external interrupt code will need.
 */
struct s3c_gpio_cfg {
	unsigned int	cfg_eint;

	s3c_gpio_pull_t	(*get_pull)(struct s3c_gpio_chip *chip, unsigned offs);
	int		(*set_pull)(struct s3c_gpio_chip *chip, unsigned offs,
				    s3c_gpio_pull_t pull);
	int		(*set_pin)(struct s3c_gpio_chip *chip, unsigned offs,
				    s3c_gpio_pull_t level);

	unsigned (*get_config)(struct s3c_gpio_chip *chip, unsigned offs);
	int	 (*set_config)(struct s3c_gpio_chip *chip, unsigned offs,
			       unsigned config);
};

#define S3C_GPIO_SPECIAL_MARK	(0xfffffff0)
#define S3C_GPIO_SPECIAL(x)	(S3C_GPIO_SPECIAL_MARK | (x))

/* Defines for generic pin configurations */
#define S3C_GPIO_INPUT	(S3C_GPIO_SPECIAL(0))
#define S3C_GPIO_OUTPUT	(S3C_GPIO_SPECIAL(1))
#define S3C_GPIO_SFN(x)	(S3C_GPIO_SPECIAL(x))

#define s3c_gpio_is_cfg_special(_cfg) \
	(((_cfg) & S3C_GPIO_SPECIAL_MARK) == S3C_GPIO_SPECIAL_MARK)

/**
 * s3c_gpio_cfgpin() - Change the GPIO function of a pin.
 * @pin pin The pin number to configure.
 * @pin to The configuration for the pin's function.
 *
 * Configure which function is actually connected to the external
 * pin, such as an gpio input, output or some form of special function
 * connected to an internal peripheral block.
 */
extern int s3c_gpio_cfgpin(unsigned int pin, unsigned int to);

#define S3C_GPIO_SLP_OUT0	((__force s3c_gpio_pull_t)0x00)
#define S3C_GPIO_SLP_OUT1	((__force s3c_gpio_pull_t)0x01)
#define S3C_GPIO_SLP_INPUT	((__force s3c_gpio_pull_t)0x02)
#define S3C_GPIO_SLP_PREV	((__force s3c_gpio_pull_t)0x03)

extern int s3c_gpio_slp_cfgpin(unsigned int pin, unsigned int to);
extern s3c_gpio_pull_t s3c_gpio_get_slp_cfgpin(unsigned int pin);

/* Define values for the pull-{up,down} available for each gpio pin.
 *
 * These values control the state of the weak pull-{up,down} resistors
 * available on most pins on the S3C series. Not all chips support both
 * up or down settings, and it may be dependant on the chip that is being
 * used to whether the particular mode is available.
 */
#define S3C_GPIO_PULL_NONE	((__force s3c_gpio_pull_t)0x00)
#define S3C_GPIO_PULL_DOWN	((__force s3c_gpio_pull_t)0x01)
#define S3C_GPIO_PULL_UP	((__force s3c_gpio_pull_t)0x02)

/**
 * s3c_gpio_setpull() - set the state of a gpio pin pull resistor
 * @pin: The pin number to configure the pull resistor.
 * @pull: The configuration for the pull resistor.
 *
 * This function sets the state of the pull-{up,down} resistor for the
 * specified pin. It will return 0 if successfull, or a negative error
 * code if the pin cannot support the requested pull setting.
*/
extern int s3c_gpio_setpull(unsigned int pin, s3c_gpio_pull_t pull);
extern int s3c_gpio_slp_setpull_updown(unsigned int pin, s3c_gpio_pull_t pull);

/**
 * s3c_gpio_getpull() - get the pull resistor state of a gpio pin
 * @pin: The pin number to get the settings for
 *
 * Read the pull resistor value for the specified pin.
*/
extern s3c_gpio_pull_t s3c_gpio_getpull(unsigned int pin);
extern s3c_gpio_pull_t s3c_gpio_slp_getpull_updown(unsigned int pin);

/**
 * s3c_gpio_setpin() - set the output of a gpio pin.
 * @pin: The pin number.
 * @level: The output level of the pin.
 *
 * This function sets the ooutput level for the
 * specified pin. It will return 0 if successfull, or a negative error
 * code if the pin cannot support the requested output/pin setting.
*/
extern int s3c_gpio_setpin(unsigned int pin, s3c_gpio_pull_t level);

#endif /* __PLAT_GPIO_CFG_H */
