#include "Arithmetics.h"

#include <../gtest/gtest.h>

TEST(TArifmethic, create_polish)
{
	ASSERT_NO_THROW();
}

TEST(TArifmethic, plus)
{
	TPolish ans;
	char* s = "2+2";
	int expRes = 4;
	int res = ans.Calculate(s);
	EXPECT_EQ(expRes, res);
}

TEST(TArifmethic, mult)
{
	TPolish ans;
	char* s = "2-2";
	int expRes = 0;
	int res = ans.Calculate(s);
	EXPECT_EQ(expRes, res);
}

TEST(TArifmethic, calc_with_brackets)
{
	TPolish ans;
	char* s = "((((2+2)*(2+2))+2)*2)";
	int expRes = 36;
	int res = ans.Calculate(s);
	EXPECT_EQ(expRes, res);
}

TEST(TArifmethic, calc_large_expression)
{
	TPolish ans;
	char* s = "(2+2)*2/2*2/2-2/2*(2+2)+2/2*2*2";
	int expRes = 4;
	int res = ans.Calculate(s);
	EXPECT_EQ(expRes, res);

}

TEST(TArifmethic, pow)
{
	TPolish ans;
	char* s = "2^2";
	int expRes = 4;
	int res = ans.Calculate(s);
	EXPECT_EQ(expRes, res);
}

