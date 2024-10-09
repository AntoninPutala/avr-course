#ifndef MATKEY_H
# define MATKEY_H

/***********************************************************
 * 
 * MATKEY library for AVR-GCC.
 * (c) 2024 Antonin Putala, MIT license
 *
 * Developed using PlatformIO and AVR 8-bit Toolchain 3.6.2.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 *
 ***********************************************************/

/**
 * @file 
 * @defgroup putala_gpio MATKEY Library <matkey.h>
 * @code #include <matkey.h> @endcode
 *
 * @brief MATKEY library for AVR-GCC.
 *
 * The library contains functions for controlling AVRs' matrix 
 * keyboard connected to gpio pin(s).
 *
 * @note Based on AVR Libc Reference Manual. Tested on ATmega328P 
 *       (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2.
 * @author Antonin Putala, Dept. of Radio Electronics, Brno University 
 *         of Technology, Czechia
 * @copyright (c) 2024 Antonin Putala, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */


/* Includes -----------------------------------------------*/
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* Function prototypes ------------------------------------*/
/**
 * @brief  Configure pins rows as outputs, columns as inputs.
 * @param  reg  Address of Data Direction Register, such as &DDRB
 * @param  nrow Number of rows in the interval 3 to 5
 * @param  ncol Number of columns in the interval 3 to (8 - nrow)
 * @return Size of keyboard in format: nrow=4 ncol=3 -> 0b0011_0100
 */
uint8_t MATKEY_setup(volatile uint8_t *reg, uint8_t nrow, uint8_t ncol);

/**
 * @brief  Translate matrix type to nrow
 * @param  type Result of MATKEY_setup()
 * @return Number of rows of matrix keyboard
 */
uint8_t MATKEY_get_nrow(uint8_t type);

/**
 * @brief  Translate matrix type to ncol
 * @param  type Result of MATKEY_setup()
 * @return Number of columns of matrix keyboard
 */
uint8_t MATKEY_get_ncol(uint8_t type);

/**
 * @brief  All rows are set to high level.
 * @param  reg  Address of Port Register, such as &PORTB
 * @param  type Result of MATKEY_setup()
 * @return none
 */
void MATKEY_reset(volatile uint8_t *reg, uint8_t type);


/**
 * @brief  Set selected pin to low value.
 * @param  reg Address of Port Register, such as &PORTB
 * @param  pos Position low level in the interval 0 to nrow-1
 * @return none
 */
void MATKEY_set_low(volatile uint8_t *reg, uint8_t pos);

/**
 * @brief  Read value from columns
 * @param  reg  Address of Pin Register, such as &PINB
 * @param  type Result of MATKEY_setup()
 * @return Pressed button column
 */
uint8_t MATKEY_col_value(volatile uint8_t *reg, uint8_t type);

/**
 * @brief  Debounce value from columns, do 4 cycle, after 10 continue
 * @param  reg  Address of Pin Register, such as &PINB
 * @param  type Result of MATKEY_setup()
 * @return Pressed debounced button column
 */
uint8_t MATKEY_deb_col_value(volatile uint8_t *reg, uint8_t type);

/**
 * @brief  Carry out reading from matrix display
 * @param  reg  Address of Pin Register, such as &PINB
 * @param  type Result of MATKEY_setup()
 * @return The order of pressed button, 16 means no button is pressed
 */
uint8_t MATKEY_read(volatile uint8_t *reg, uint8_t type);

/** @} */

#endif