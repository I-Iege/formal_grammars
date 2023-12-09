#include <gtest/gtest.h>

import formal_languages;

TEST(TEST_SIGN, sign1)
{
    sign S("S", false);
    sign s("S", true);

    EXPECT_EQ(s, S);

    sign S2("S", false);
    sign s2("s", false);

    EXPECT_NE(s2, S2);
    EXPECT_GT(s2, S2);
}
