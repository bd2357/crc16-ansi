#include "unity.h"
#include "crc16.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// for testing slower soft version
uint16_t  Update_CRC16soft(uint16_t CRC, uint8_t Data);

static uint16_t  softCalculate_CRC16(uint8_t* ptr, uint16_t length)
{
  uint16_t  crc16 = CRC16_INITIAL_VALUE;
        
  while(length--)
  {
    crc16 = Update_CRC16soft(crc16, *(ptr++)); 
  }
  
  return  crc16;
}







// make a structure with at least 16 bits at the end for the CRC16
// the CRC will be placed in the last two bytes of the space allocated
// for the structure not necessarily the address offset of a named field at the
// end.
typedef struct
{
    uint32_t value1;
    uint8_t value2, value3, vaule4;
    uint16_t crc16Space; // not necessarily where crc will land 
} data_t;

uint8_t testVec[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
uint8_t testVec2[] = "This is a test of CRC16 using initial value 0xFFFF and Polynomial 0x8005.";
void test_result(void)
{
    TEST_ASSERT_EQUAL_UINT16(0x4b37, Calculate_CRC16(testVec, sizeof(testVec)));
    TEST_ASSERT_EQUAL_UINT16(0xe15b, Calculate_CRC16("This is a test", 14));
    TEST_ASSERT_EQUAL_UINT16(0xe2ba, Calculate_CRC16(testVec2, sizeof(testVec2)-1));
    // verify we get same results from soft version
    TEST_ASSERT_EQUAL_UINT16(0xe2ba, softCalculate_CRC16(testVec2, sizeof(testVec2)-1));
}

// append places the crc in the last two bytes of the passed data buffer.
// the order and orientation is such that calculating the crc over the
// subsequent buffer will return 0.
void test_append(void)
{
    data_t data = {1,2,3,4,5};
    // may or may not overwrite the 5 depending on packing
    Append_CRC16((uint8_t*)&data, sizeof(data));
    //printf("%x, %x, %x, %x\n", data.crc16Space, sizeof(data), ((uint8_t*)&data)[sizeof(data)-2],((uint8_t*)&data)[sizeof(data)-1]);
    TEST_ASSERT_EQUAL_UINT16(0, Calculate_CRC16((uint8_t*)&data,sizeof(data)));
    //TEST_ASSERT_NOT_EQUAL(5, data.crc16Space); // depends on packing
    // verify we get same results from soft version
    TEST_ASSERT_EQUAL_UINT16(0, softCalculate_CRC16((uint8_t*)&data,sizeof(data)));
}

void test_special(void)
{

    uint8_t buffer1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8_t buffer2[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};

   
    // make sure we can deal with buffers full of zeros.
    uint16_t crc = Calculate_CRC16(buffer1, sizeof(buffer1));
    //printf("%x",crc);
    TEST_ASSERT_NOT_EQUAL(0, crc);
    
    // make sure we can deal with buffers full of ones
    crc = Calculate_CRC16(buffer2, sizeof(buffer2));
    //printf("%x",crc);
    TEST_ASSERT_NOT_EQUAL(0, crc);
    TEST_ASSERT_NOT_EQUAL(0xffff, crc);

}