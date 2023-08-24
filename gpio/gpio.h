#ifndef __PIC_GPIO_H__
#define __PIC_GPIO_H__

#include "../config.h"

#ifdef PIC_GPIO_ENABLED

typedef enum {
    GPIO_MODE_OUTPUT = 0,
    GPIO_MODE_INPUT
} GPIO_MODE;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;

typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_COUNT
} GPIO_PORT;

typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_COUNT
} GPIO_PIN;

/**
 * @brief Initialize GPIO
 * 
 * @param port This parameter can be one of GPIO_PORT_X where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param pin specifies the port bit to be written.
 *          This parameter can be one of GPIO_PIN_x where x can be (0..8).
 * @param mode This parameter can be one of the GPIO_MODE_x where x can be (OUTPUT, INPUT)
 */
#define gpio_pin_init(port, pin, mode) \
    do { \
        *(volatile uint8_t *)(&TRISA + port) = (*(volatile uint8_t *)(&TRISA + port) & ~(1 << pin)) | (mode << pin); \
    } while (0)

/**
 * @brief Set GPIO output level
 * 
 * @param port This parameter can be one of GPIO_PORT_X where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param pin specifies the port bit to be written.
 *          This parameter can be one of GPIO_PIN_x where x can be (0..8).
 * @param pin_state This parameter can be one of the GPIO_PIN_x where x can be (GPIO_PIN_RESET, GPIO_PIN_SET)
 */
#define gpio_pin_write(port, pin, pin_state) \
    do { \
        *(volatile uint8_t *)(&PORTA + port) = (*(volatile uint8_t *)(&PORTA + port) & ~(1 << pin)) | (pin_state << pin); \
    } while (0)

/**
 * @brief Set GPIO input level
 * 
 * @param port This parameter can be one of GPIO_PORT_X where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param pin specifies the port bit to be written.
 *          This parameter can be one of GPIO_PIN_x where x can be (0..8).
 * @param pin_state This parameter can be one of the GPIO_PIN_x where x can be (GPIO_PIN_RESET, GPIO_PIN_SET)
 */
#define gpio_pin_set(port, pin) \
    do { \
        *(volatile uint8_t *)(&PORTA + port) |= (1 << pin); \
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
        *(volatile uint8_t *)(&PORTA + port) &= ~(1 << pin); \
    } while (0)

/**
 * @brief Get GPIO input level
 * 
 * @param port GPIO port: A, B, C, D, E
 * @param pin GPIO pin: 0, 1, 2, 3, 4, 5, 6, 7
 * @return uint8_t GPIO input level: 1 - high, 0 - low
 */
#define gpio_pin_read(port, pin) \
    ((*(volatile uint8_t *)(&PORTA + port) & (1 << pin)) >> pin)

#endif // PIC_GPIO_ENABLED

#endif // __PIC_GPIO_H__