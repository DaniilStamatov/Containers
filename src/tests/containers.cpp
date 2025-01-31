#include "tests.h"

class ContainerTests : public ::testing::Test {
 protected:
  ContainerTests() {
    // Код который нужно запустить перед каждым тестом
  }
};

TEST_F(ContainerTests, TestOfATest) { EXPECT_EQ(1, 1); }
