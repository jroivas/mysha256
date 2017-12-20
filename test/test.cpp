#include "test.hh"
#include "boxes.hh"
#include "message.hh"

TEST_MAIN(

  TEST_SUITE(Ch box,
    TEST_CASE(Ch box all zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0, 0, 0), 0)
    )
    TEST_CASE(Ch box one zero zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xFFFFFFFF, 0, 0), 0)
    )
    TEST_CASE(Ch box one one zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xFFFFFFFF, 0xFFFFFFFF, 0), 0xFFFFFFFF)
    )
    TEST_CASE(Ch box one one one input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF)
    )
    TEST_CASE(Ch box half one zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xAAAAAAAA, 0xFFFFFFFF, 0), 0xAAAAAAAA)
    )
    TEST_CASE(Ch box one half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555), 0xAAAAAAAA)
    )
    TEST_CASE(Ch box zero half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0x00000000, 0xAAAAAAAA, 0x55555555), 0x55555555)
    )
    TEST_CASE(Ch box half0 half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ch(0xF0F0F0F0, 0xAAAAAAAA, 0x55555555), 0xA5A5A5A5)
    )
  )

  TEST_SUITE(Ma box,
    TEST_CASE(Ma box all zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0, 0, 0), 0)
    )
    TEST_CASE(Ma box one zero zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xFFFFFFFF, 0, 0), 0)
    )
    TEST_CASE(Ma box one one zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xFFFFFFFF, 0xFFFFFFFF, 0), 0xFFFFFFFF)
    )
    TEST_CASE(Ma box one one one input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF)
    )
    TEST_CASE(Ma box half one zero input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xAAAAAAAA, 0xFFFFFFFF, 0), 0xAAAAAAAA)
    )
    TEST_CASE(Ma box one half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555), 0xFFFFFFFF)
    )
    TEST_CASE(Ma box zero half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0x00000000, 0xAAAAAAAA, 0x55555555), 0)
    )
    TEST_CASE(Ma box half0 half1 half2 input,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xF0F0F0F0, 0xAAAAAAAA, 0x55555555), 0xF0F0F0F0)
    )
    TEST_CASE(Ma box output third,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xFFFFFFFF, 0x0, 0x12345678), 0x12345678)
    )
    TEST_CASE(Ma box output propely on random inputs,
      TEST_ASSERT_EQUALS(sha::Box::Ma(0xABCDEF10, 0xeffe1337, 0x12345678), 0xabfc5730)
    )
  )

  TEST_SUITE(S0 box,
    TEST_CASE(S0 box zero input,
      TEST_ASSERT_EQUALS(sha::Box::S0(0), 0)
    )
    TEST_CASE(S0 box one input,
      TEST_ASSERT_EQUALS(sha::Box::S0(1), 0x40080400)
    )
    TEST_CASE(S0 box full input,
      TEST_ASSERT_EQUALS(sha::Box::S0(0xFFFFFFFF), 0xFFFFFFFF)
    )
    TEST_CASE(S0 box one zero at end,
      TEST_ASSERT_EQUALS(sha::Box::S0(0xFFFFFFFE), 0xbff7fbff)
    )
    TEST_CASE(S0 box one zero at begin,
      TEST_ASSERT_EQUALS(sha::Box::S0(0x7FFFFFFF), 0xDFFBFDFF)
    )
    TEST_CASE(S0 box random input,
      TEST_ASSERT_EQUALS(sha::Box::S0(0xABE1337F), 0xF5C8ED79)
    )
  )

  TEST_SUITE(S1 box,
    TEST_CASE(S1 box zero input,
      TEST_ASSERT_EQUALS(sha::Box::S1(0), 0)
    )
    TEST_CASE(S1 box one input,
      TEST_ASSERT_EQUALS(sha::Box::S1(1), 0x04200080)
    )
    TEST_CASE(S1 box full input,
      TEST_ASSERT_EQUALS(sha::Box::S1(0xFFFFFFFF), 0xFFFFFFFF)
    )
    TEST_CASE(S1 box one zero at end,
      TEST_ASSERT_EQUALS(sha::Box::S1(0xFFFFFFFE), 0xFBDFFF7F)
    )
    TEST_CASE(S1 box one zero at begin,
      TEST_ASSERT_EQUALS(sha::Box::S1(0x7FFFFFFF), 0xFDEFFFBF)
    )
    TEST_CASE(S1 box random input,
      TEST_ASSERT_EQUALS(sha::Box::S1(0xABE1337F), 0x61c3473e)
    )
  )

  TEST_SUITE(message import,
    TEST_CASE(import from empty string,
      uint32_t res[16] = {0};
      TEST_ASSERT_EQUALS_ARRAY(sha::Message::import(""), res, 16)
    )
    TEST_CASE(import from string,
      uint32_t res[16] = {0};
      res[0] = 0x48656c6c;
      res[1] = 0x6f20776f;
      res[2] = 0x726c6400;
      TEST_ASSERT_EQUALS_ARRAY(sha::Message::import("Hello world"), res, 16)
    )
  )
)
