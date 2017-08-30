#include "unity.h"
#include "crc8.h"
#include <stdio.h>


void dumpTable(void)
{
    for (int r =0; r<16; r++)
    {
        for (int c =0; c<16; c++)
        {
            printf("0x%02x,", crc8Table[(r<<4)+c]);
        }
        printf("\n");
    }
    
}

void setUp(void)
{
}

void tearDown(void)
{
}

char test[10]="123456789";

void test_from_source(void)
{
    crc8Init(0x1d);
    TEST_ASSERT_EQUAL_UINT8(0xf, crc8(0x00, 0xC2)  );
    uint8_t crc = crc8(0,1);
    TEST_ASSERT_EQUAL_UINT8(0x76, crc8(crc, 0x02)  );
    /*
    printf("gen 0x1d\n");
    for(int i=0; i<256; i++)
    {
        printf("%02x, %02x\n", i, crc8Table[i]);
    }
    */

}


void test_from_source2(void)
{
    uint8_t buf[2] = {1,2};
    crc8Init(0x1d);
    
    TEST_ASSERT_EQUAL_UINT8(0x76, calcCrc8(0, buf, sizeof(buf))  );
}

void test_k83(void)
{
    crc8Init(0x7);
    TEST_ASSERT_EQUAL_UINT8(0xf4, calcCrc8(0, test, 9)  );
}

void test_kea(void)
{
    crc8Init(0xd5);
    TEST_ASSERT_EQUAL_UINT8(0xbc, calcCrc8(0, test, 9)  );
}

void test_iCode(void)
{
    crc8Init(0x1d);
    TEST_ASSERT_EQUAL_UINT8(0x7e, calcCrc8(0xfd, test, 9)  );
}

void test_build2f(void)
{
    
    crc8Init(0x2f);
    TEST_ASSERT_EQUAL_UINT8(0x3e, test[9]=calcCrc8(0x00, test, 9)  );
    TEST_ASSERT_EQUAL_UINT8(0, calcCrc8(0x00, test, 10)  );
    test[4]++;
    TEST_ASSERT_NOT_EQUAL(0, calcCrc8(0x00, test, 10)  );
    test[4]++;
    TEST_ASSERT_NOT_EQUAL(0, calcCrc8(0x00, test, 10)  );
    test[4]++;
    TEST_ASSERT_NOT_EQUAL(0, calcCrc8(0x00, test, 10)  );
    test[4]++;
    TEST_ASSERT_NOT_EQUAL(0, calcCrc8(0x00, test, 10)  );
    test[4] = '5';
    TEST_ASSERT_EQUAL_UINT8(0, calcCrc8(0x00, test, 10)  );

    dumpTable();
}

void test_table(void)
{
    crc8RestoreHardTable();  // default is 0x2f
    test[sizeof(test)-1]=calcCrc8(0xec, test, sizeof(test)-1);
    TEST_ASSERT_EQUAL_UINT8(0, calcCrc8(0xec, test, sizeof(test))  );
}