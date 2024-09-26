
// Online C Compiler - Build, Compile and Run your C programs online in your favorite browser

#include <avr/io.h>

// Function declaration (prototype)
uint16_t calculate(uint8_t, uint8_t);

int main(void)
{
    uint8_t a = 210;
    uint8_t b = 15;
    uint16_t c;

    // Function call
    c = calculate(a, b);
    
    // Infinite loop
    while (1) ;

    // Will never reach this
    return 0;
}

// Function definition (body)
uint16_t calculate(uint8_t x, uint8_t y)
{
    uint16_t result;    // result = x^2 + 2xy + y^2

    result = x*x;
    result += 2*x*y;
    result += y*y;
    return result;
}
