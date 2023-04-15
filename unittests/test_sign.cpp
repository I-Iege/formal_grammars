#include <gtest/gtest.h>
#include "sign.h"

TEST(TEST_SIGN, sign1 ) {
    
    sign S("S", false);
    sign s("S", true);
    
    EXPECT_TRUE( s == S );
    
    sign S2("S", false);
    sign s2("s", false);
    
    EXPECT_TRUE( s2 != S2 );
    EXPECT_TRUE( s2 > S2 );
}
