#include "test.hh"
#include "boxes.hh"

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

)
