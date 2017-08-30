# crc16-ansi

Functions to use crc16-ansi generator polynomial 0x8005 (0xA001 reversed)
Useful in serial com validations and flash block validations.

For short serial messages can also be used to detect message completion by
detecting when the crc goes to 0. 

Also added a crc8 with generator polynomial:
    
    x^8+x^5+x^3+x^2+x+1 (Baicheva C2) 

referred to as 0x97 by Koopman - "Cyclic Redundancy Code (CRC) Polynomial Selection For Embedded Networks"
which can detect burst errors of up to 4 bits in messages up to 119 bits and has reasonable detection up to 2048 bits.
Koopman 0x97 is 0x2f in traditional representation.

The test code can be used to generate a new table if you want a different polynomial.
