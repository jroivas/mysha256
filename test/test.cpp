#include "test.hh"
#include "boxes.hh"
#include "message.hh"
#include "hash.hh"

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
      TEST_ASSERT_EQUALS(sha::Box::S1(0xABE1337F), 0x61C3473E)
    )
  )

  TEST_SUITE(I0 box,
    TEST_CASE(I0 box zero input,
      TEST_ASSERT_EQUALS(sha::Box::I0(0), 0)
    )
    TEST_CASE(I0 box full input,
      TEST_ASSERT_EQUALS(sha::Box::I0(0xFFFFFFFF), 0x1FFFFFFF)
    )
    TEST_CASE(I0 random input,
      TEST_ASSERT_EQUALS(sha::Box::I0(0xABE1337F), 0xA6F40EF1)
    )
  )
  TEST_SUITE(I1 box,
    TEST_CASE(I1 box zero input,
      TEST_ASSERT_EQUALS(sha::Box::I1(0), 0)
    )
    TEST_CASE(I1 box full input,
      TEST_ASSERT_EQUALS(sha::Box::I1(0xFFFFFFFF), 0x3FFFFF)
    )
    TEST_CASE(I1 random input,
      TEST_ASSERT_EQUALS(sha::Box::I1(0xABE1337F), 0xBFFAD8C0)
    )
  )

  uint32_t alphabet[16] = {0};
  alphabet[0] = 0x61616161;
  alphabet[1] = 0x62626262;
  alphabet[2] = 0x63636363;
  alphabet[3] = 0x64646464;
  alphabet[4] = 0x65656565;
  alphabet[5] = 0x66666666;
  alphabet[6] = 0x67676767;
  alphabet[7] = 0x68686868;
  alphabet[8] = 0x69696969;
  alphabet[9] = 0x6a6a6a6a;
  alphabet[10] = 0x6b6b6b6b;
  alphabet[11] = 0x6c6c6c6c;
  alphabet[12] = 0x6d6d6d6d;
  alphabet[13] = 0x6e6e6e6e;
  alphabet[14] = 0x6f6f6f6f;
  alphabet[15] = 0x70707070;
  TEST_SUITE(Chunk creation,
    TEST_CASE(import from empty string check size,
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("");
      TEST_ASSERT_EQUALS(chunks.size(), 1)
    )
    TEST_CASE(import from empty string check zero,
      uint32_t res[16] = {0};
      res[0] = 0x80000000;
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("");
      TEST_ASSERT_EQUALS_ARRAY(chunks[0].wordPtr(), res, 16)
    )
    TEST_CASE(import hello world,
      uint32_t res[16] = {0};
      res[0] = 0x48656c6c;
      res[1] = 0x6f20776f;
      res[2] = 0x726c6480;
      res[15] = 0x00000058;
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("Hello world");
      TEST_ASSERT_EQUALS_ARRAY(chunks[0].wordPtr(), res, 16)
    )
    std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssss");
    TEST_CASE(import multiple blocks,
      TEST_ASSERT_EQUALS(chunks.size(), 2);
    )
    TEST_CASE(import alphabet to full block,
      TEST_ASSERT_EQUALS_ARRAY(chunks[0].wordPtr(), alphabet, 16)
    )
    TEST_CASE(compare data of first chunk,
      TEST_ASSERT_EQUALS_ARRAY(chunks[0].wordPtr(), alphabet, 16)
    )

    TEST_CASE(compare data of second chunk,
      uint32_t res[16] = {0};
      res[0] = 0x71717171;
      res[1] = 0x72727272;
      res[2] = 0x73737373;
      res[3] = 0x80000000;
      TEST_ASSERT_EQUALS_ARRAY(chunks[1].wordPtr(), res, 8)
    )
  )

  TEST_SUITE(Message schedule from chunk,
    std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnoooopppp");
    sha::Message::Schedule schedule(chunks[0]);
    TEST_CASE(Chunk is copied,
      TEST_ASSERT_EQUALS_ARRAY(schedule.wordPtr(), alphabet, 16);
    )
    TEST_CASE(Rest of schedule is generated,
      uint32_t res[16] = {0};
      res[0] = 0x761d5d5c;
      res[1] = 0x166a6a69;
      TEST_ASSERT_EQUALS_ARRAY_INDEX(schedule.wordPtr(), res, 16, 2);
    )
  )

  TEST_SUITE(Hash,
    TEST_CASE(Empty hash,
      sha::Hash hash;
      uint32_t res[8] = {0};
      res[0] = 0x6a09e667;
      res[1] = 0xbb67ae85;
      res[2] = 0x3c6ef372;
      res[3] = 0xa54ff53a;
      res[4] = 0x510e527f;
      res[5] = 0x9b05688c;
      res[6] = 0x1f83d9ab;
      res[7] = 0x5be0cd19;
      TEST_ASSERT_EQUALS_ARRAY(hash.get(), res, 8);
    )

    TEST_CASE(Empty rounds hash,
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("");
      sha::Hash hash;
      hash.round(chunks[0]);
      uint32_t res[8] = {0};
      res[0] = 0xe3b0c442;
      res[1] = 0x98fc1c14;
      res[2] = 0x9afbf4c8;
      res[3] = 0x996fb924;
      res[4] = 0x27ae41e4;
      res[5] = 0x649b934c;
      res[6] = 0xa495991b;
      res[7] = 0x7852b855;
      TEST_ASSERT_EQUALS_ARRAY(hash.get(), res, 8);
    )

    TEST_CASE(Hash round with one chunk,
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("aaaabbbbccccddddeeeeffffgggghhhhiiiijjjj");
      sha::Hash hash;
      hash.round(chunks[0]);

      uint32_t res[8] = {0};
      res[0] = 0x66dd9cb2;
      res[1] = 0x553a3835;
      res[2] = 0x78cf2352;
      res[3] = 0x131981dd;
      res[4] = 0x3f0d296c;
      res[5] = 0x1e1bf58e;
      res[6] = 0xefd7293a;
      res[7] = 0xd2d71fec;
      TEST_ASSERT_EQUALS_ARRAY(hash.get(), res, 8);
    )

    TEST_CASE(Hash round with two chunks,
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnoooopppp");
      sha::Hash hash;
      hash.round(chunks[0]);
      hash.round(chunks[1]);

      uint32_t res[8] = {0};
      res[0] = 0x37e4e3c0;
      res[1] = 0x2a59b5f8;
      res[2] = 0x2b095a3c;
      res[3] = 0x75acf04a;
      res[4] = 0x0bad972e;
      res[5] = 0xf5488999;
      res[6] = 0xa71e99df;
      res[7] = 0x56c28772;
      TEST_ASSERT_EQUALS_ARRAY(hash.get(), res, 8);
    )

    TEST_CASE(Hash round with all chunks,
      std::vector<sha::Message::Chunk> chunks = sha::Message::Chunk::create("aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnoooopppp");
      sha::Hash hash;
      hash.round(chunks);

      uint32_t res[8] = {0};
      res[0] = 0x37e4e3c0;
      res[1] = 0x2a59b5f8;
      res[2] = 0x2b095a3c;
      res[3] = 0x75acf04a;
      res[4] = 0x0bad972e;
      res[5] = 0xf5488999;
      res[6] = 0xa71e99df;
      res[7] = 0x56c28772;
      TEST_ASSERT_EQUALS_ARRAY(hash.get(), res, 8);
    )
  )
)
