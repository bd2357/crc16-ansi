/**
@file crc16.h
@brief Include file for crc.c

Contains defines for initial values and polynomials.

*/


#ifndef __CRC16_H__
#define __CRC16_H__

#include <stdint.h>
#include <stddef.h>

/**
@defgroup crc
@{
*/

// For information only, table is hardcoded to P_16 = 0xA001
#define CRC16_INITIAL_VALUE   0xFFFF
#define P_16                  0xA001

/**
 *  @brief Add a byte to a CRC16
 *  
 *  @param [in] CRC The ongoing CRC value
 *  @param [in] Data the byte to add to the CRC
 *  @return the updated CRC value
 *  
 *  @details Details
 */
uint16_t  Update_CRC16(uint16_t CRC, uint8_t Data);

/**
 *  @brief Calculate a CRC16 over the byte buffer.
 *  
 *  @param [in] ptr pointer to a buffer of bytes.
 *  @param [in] length number of bytes to include in crc
 *  @return The CRC16 value
 *  
 *  @details 
 */
uint16_t  Calculate_CRC16(uint8_t const * ptr, size_t length);

/**
 *  @brief calculate and place a crc16 into the last two bytes of the
 *  passed buffer.
 *  
 *  @param [in] buf pointer to the buffer 
 *  @param [in] totalLen the total length of the buffer including the 
 *                       two byte CRC
 *  
 *  @details This function places a two byte CRC, low byte, high byte order
 *  into the last two positions of the passed array. It calculates the CRC16
 *  over all but the last two bytes. The byte order of the CRC16 is designed
 *  such that if the CRC16 is taken over totalLen, the correct result should
 *  be zero (0). e.g.  
 *  AppendCRC16(buf, sizeof(buf));
 *  ASSERT(Calculate_CRC16(buf,sizeof(buf)) == 0);
 */
void Append_CRC16(uint8_t *buf, size_t totalLen);


/**
@}
*/

#endif  /* __CRC_H__ */
