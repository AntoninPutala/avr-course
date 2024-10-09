/***********************************************************
 * 
 * GPIO library for AVR-GCC.
 * (c) 2024 Antonin Putala, MIT license
 *
 * Developed using PlatformIO and AVR 8-bit Toolchain 3.6.2.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 *
 ***********************************************************/

/* Defines ------------------------------------------------*/
#include <matkey.h>

#define WAIT_MATRIX_KEYBOARD_DEBOUNCE 1000 // in us
#define NUMBER_DEB_CYCLE 4
#define NUMBER_ALL_CYCLE 10

/* Function definitions -----------------------------------*/
/***********************************************************
 * Function: MATKEY_setup()
 * Purpose:  Configure pins for matrix display
 * Input(s): reg  - Address of Data Direction Register, such as &DDRB
 *           nrow - Number of rows in the interval 3 to 5
 *           ncol - Number of columns in the interval 3 to (8 - nrow)
 * Returns:  Size of keyboard in format: nrow=4 ncol=3 -> 0b0011_0100
 ***********************************************************/
uint8_t MATKEY_setup(volatile uint8_t *reg, uint8_t nrow, uint8_t ncol)
{
    uint8_t i;
    uint8_t j;

    // Rows are set as outputs
    for (i = 0; i < nrow; i++)
    {
        *reg |= (1 << i);
    }

    // Columns are set as inputs
    for (j = 0; j < ncol; j++)
    {
        *reg &= ~(1<<(nrow+j));  // Data Direction Register
    }

    reg++;                             // Change pointer to Data Register

    // Pullups of inputs are disable
    for (j = 0; j < ncol; j++)
        {
        *reg = *reg & ~(1<<(nrow+j));  // Data Register
        }

    return (nrow | (ncol << 4));
}


/***********************************************************
 * Function: MATKEY_get_nrow()
 * Purpose:  Translate matrix type to nrow
 * Input(s): type - Result of MATKEY_setup()
 * Returns:  Number of rows of matrix keyboard
 ***********************************************************/
uint8_t MATKEY_get_nrow(uint8_t type)
{
    return type & ((1 << 2) | (1 << 1) | (1 << 0));
}


/***********************************************************
 * Function: MATKEY_get_ncol()
 * Purpose:  Translate matrix type to ncol
 * Input(s): type - Result of MATKEY_setup()
 * Returns:  Number of columns of matrix keyboard
 ***********************************************************/
uint8_t MATKEY_get_ncol(uint8_t type)
{
    return (type & ((1 << 6) | (1 << 5) | (1 << 4))) >> 4;
}


/***********************************************************
 * Function: MATKEY_reset()
 * Purpose:  Set all rows to high level
 * Input(s): reg  - Address of Port Register, such as &PORTB
 *           type - Result of MATKEY_setup()
 * Returns:  none
 ***********************************************************/
void MATKEY_reset(volatile uint8_t *reg, uint8_t type)
{
    // to high level is set all pins (0 to nrow)
    // nrow is contained in last 3 bits 
    for (uint8_t i = 0; i < (type & ((1 << 2) | (1 << 1) | (1 << 0))); i++)
    {
        *reg |= (1<<i);
    }
}


/***********************************************************
 * Function: MATKEY_set_low()
 * Purpose:  Set selected pin to low value
 * Input(s): reg - Address of Port Register, such as &PORTB
 *           pos - Position low level in the interval 0 to nrow-1
 * Returns:  none
 ***********************************************************/
void MATKEY_set_low(volatile uint8_t *reg, uint8_t pos)
{
    *reg &= ~(1<<pos);
}


/***********************************************************
 * Function: MATKEY_col_value()
 * Purpose:  Set selected pin to low value
 * Input(s): reg  - Address of Pin Register, such as &PINB
 *           type - Result of MATKEY_setup()
 * Returns:  Pressed button column
 ***********************************************************/
uint8_t MATKEY_col_value(volatile uint8_t *reg, uint8_t type)
{
    uint8_t nrow = MATKEY_get_nrow(type);
    uint8_t ncol = MATKEY_get_ncol(type);

    for (uint8_t i = 0; i < ncol; i++)
    {
        if ((*reg & (1<<(nrow+i))) == 0) 
        {
            return i;
        }
    }
    return 5;
}


/***********************************************************
 * Function: MATKEY_deb_col_value()
 * Purpose:  Debounce value from columns, do 4 cycle, after 10 continue
 * Input(s): reg  - Address of Pin Register, such as &PINB
 *           type - Result of MATKEY_setup()
 * Returns:  Pressed debounced button column
 ***********************************************************/
uint8_t MATKEY_deb_col_value(volatile uint8_t *reg, uint8_t type)
{
    uint8_t col_value;  // last_value
    uint8_t new_value;  // new_value
    uint8_t count = 0;  // the number of consecutive identical values 

    col_value = MATKEY_col_value(reg, type);     // first test of buttons

    for (uint8_t i = 0; i < NUMBER_ALL_CYCLE; i++)
    {
        _delay_us(WAIT_MATRIX_KEYBOARD_DEBOUNCE);   // next test after 1ms
        new_value = MATKEY_col_value(reg, type);

        if (new_value == col_value)                 // if values are identical, count is incremented
        {
            count++;

            if (count > (NUMBER_DEB_CYCLE-2))       // more than 2 means 4 identical values
            {
                return new_value;
            }
        }
        else
        {
            count = 0;                              // not equal values, reset counter
        }

        col_value = new_value;                      // current value is moved to last value
    }
    
    return 5;                                       // undefined state
}


/***********************************************************
 * Function: MATKEY_read()
 * Purpose:  Carry out reading from matrix display
 * Input(s): reg  - Address of Pin Register, such as &PINB
 *           type - Result of MATKEY_setup()
 * Returns:  The order of pressed button, 16 means no button is pressed
 ***********************************************************/
uint8_t MATKEY_read(volatile uint8_t *reg, uint8_t type)
{
    uint8_t col_value;
    uint8_t nrow = MATKEY_get_nrow(type);
    uint8_t ncol = MATKEY_get_ncol(type);

    MATKEY_reset(reg+2,type);

    for (uint8_t i = 0; i < nrow; i++)
    {
        MATKEY_set_low(reg+2, i);
        col_value = MATKEY_deb_col_value(reg, type);

        if (col_value < ncol)
        {
            return i*ncol + col_value;
        }
        MATKEY_reset(reg+2,type);
    }

    return 16;
}