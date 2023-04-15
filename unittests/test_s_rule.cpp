#include <gtest/gtest.h>
#include "s_rule.h"

TEST(TEST_S_RULE, srule1) 
{
    sign s("S", false);
    sign_list signList1 = {s, s};
    signList1.push_back(s);
    s_rule rule1(s, signList1, 0);

    s_rule rule2(s, signList1, 1);
    s_rule rule3(s, {s, s, s}, 0);

    EXPECT_FALSE(rule1 == rule2);
    EXPECT_FALSE(rule1 == rule3);


}
