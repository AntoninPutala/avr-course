# avr-course

## Header

## Body

### Introduction
This is __github__ of my _avr course_.

### Aims
* Learn programming.
* Learn working with Github.
* Learn working with MCU.

### Codes
```python Example python
import numpy
a = 10
b = 5
c = a + b
print(c)
```

```c Example C
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
                        // is connected
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
```

## Tables
|Position|Name|Value|Number|
|---|---|---|---|
|R1|resistor|100R|1|
|R2,R3|resistor|220R|2|
|R4,R6|resistor|1k|2|
|R5,R8|resistor|2k2|2|
|R7|resistor|10k|1|

## Appendix

## Reference
1. [wikipedia.org](https://cs.wikipedia.org/wiki/Hlavn%C3%AD_strana)
2. [seznam.cz](https://www.seznam.cz/)
3. [Copilot](https://www.bing.com/chat?q=copilot&sendquery=1&FORM=SCCODX)
