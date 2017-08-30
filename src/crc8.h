/**
 *  @file crc8.h
 *  @brief CRC8 calculator for our inter processor bus.
 *  adaptable to any polynomial, we are using generator 
 *  x^8+x^5+x^3+x^2+x+1 (Baicheva C2) referred to as 0x97 by Koopman -
 *  "Cyclic Redundancy Code (CRC) Polynomial Selection For Embedded Networks"
 *  which can detect burst errors of up to 4 bits in messages up to 119 bits and
 *  has reasonable detection up to 2048 bits.
 *  Koopman 0x97 is 0x2f in traditional representation.
 *  
 */
#ifndef _CRC8_H
#define _CRC8_H

#include <stdint.h>
#include <stddef.h>


#ifdef CRC_HARD_TABLE
extern uint8_t const * const crc8Table;
#else
extern uint8_t const *crc8Table;  
void crc8Init(uint8_t gen);  
#endif    

static inline uint8_t crc8(uint8_t lastCrc, uint8_t val)
{
    return crc8Table[val ^ lastCrc];
}

// add val to crc
//uint8_t crc8(uint8_t crc, uint8_t val);
// change crc8 value so crc8(crc,val) == 0
uint8_t crc8place(uint8_t val);

uint8_t calcCrc8(uint8_t lastCrc, uint8_t *buf, size_t bufLen);
void crc8RestoreHardTable(void);

#endif // _CRC8_H
