#include <gtest/gtest.h>
#include "grammar.h"
#include "greibach.h"
#include <utility>
TEST(TEST_GREIBACH_ALG, greibach1)
{
    grammar g("../../../../input/t2.txt");
    grammar g2 = {{
                      {"S"},
                      {"A"},
                      {"B"},
                      {"C"},
                      {"D"},
                      {"E"},
                  },
                  {
                      {"a"},
                      {"b"},
                      {"c"},
                      {"+"},
                      {"("},
                      {")"},
                  },
                  {
                      {{"S"},
                       {{
                            {"S", false},
                            {"C", false},
                            {"A", false},
                        },
                        {
                            {"A", false},
                        }}},
                  },
                  {"S", false}};
    greibach g_alg(g);
    grammar result("../../../../input/t2_result.txt");
    EXPECT_EQ(result, g_alg.get_result());
}
