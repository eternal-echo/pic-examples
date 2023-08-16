#ifndef __PIC_GPIO_H__
#define __PIC_GPIO_H__

#include "../config.h"

#ifdef PIC_GPIO_ENABLED

#define GPIO_OUTPUT 0
#define GPIO_INPUT 1

/**
 * @brief Initialize GPIO
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @param dir GPIO direction: 1 - input, 0 - output
 */
#define gpio_pin_init(port, pin, dir) \
    do { \
        TRIS##port = (TRIS##port & ~(1 << pin)) | (dir << pin); \
    } while (0)

/**
 * @brief Set GPIO output level
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @param level GPIO output level: 1 - high, 0 - low
 */
#define gpio_pin_write(port, pin, level) \
    do { \
        PORT##port = (PORT##port & ~(1 << pin)) | (level << pin); \
    } while (0)

/**
 * @brief Set GPIO input level
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @param level GPIO input level: 1 - high, 0 - low
 */
#define gpio_pin_set(port, pin) \
    do { \
        PORT##port |= (1 << pin); \
    } while (0)

/**
 * @brief Clear GPIO input level
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @param level GPIO input level: 1 - high, 0 - low
 */
#define gpio_pin_clear(port, pin) \
    do { \
        PORT##port &= ~(1 << pin); \
    } while (0)

/**
 * @brief Get GPIO input level
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @return uint8_t GPIO input level: 1 - high, 0 - low
 */
#define gpio_pin_read(port, pin) \
    (PORT##port & (1 << pin))

#endif // PIC_GPIO_ENABLED

#endif // __PIC_GPIO_H__