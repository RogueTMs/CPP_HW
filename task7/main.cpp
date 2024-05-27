#include "expression.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Expression, base) {

    Expression *e = new Add(new Var("x"), new Add(new Val(10), new Var("y")));

    ASSERT_EQ(e->get_str(), "x+10+y");
    Expression *edx = e->diff("x");
    Expression *edy = e->diff("y");
    ASSERT_EQ(edx->get_str(), "1+0+0");
    ASSERT_EQ(edy->get_str(), "0+0+1");

    delete e;
    delete edx;
    delete edy;
}

TEST(Expression, Exponent_diff) {
    Expression *e = new Exponent(new Var("x"));

    Expression *edx = e->diff("x");
    Expression *edy = e->diff("y");
    ASSERT_EQ(edx->get_str(), "(1)*(e^x)");
    ASSERT_EQ(edy->get_str(), "(0)*(e^x)");

    delete e;
    delete edx;
    delete edy;
}

TEST(Expression, Mult_diff) {
    Expression *e = new Mult(new Var("x"), new Val(5));

    Expression *edx = e->diff("x");
    ASSERT_EQ(edx->get_str(), "(1)*(5)+(x)*(0)");

    delete e;
    delete edx;
}

TEST(Expression, Sub_diff) {
    Expression *e = new Sub(new Var("x"), new Val(5));

    Expression *edx = e->diff("x");
    ASSERT_EQ(edx->get_str(), "1-0");

    delete e;
    delete edx;
}

TEST(Expression, Add_diff) {
    Expression *e = new Add(new Var("x"), new Val(5));

    Expression *edx = e->diff("x");
    ASSERT_EQ(edx->get_str(), "1+0");

    delete e;
    delete edx;
}

TEST(Expression, Div_diff) {
    Expression *e = new Div(new Var("x"), new Val(5)); // x/5

    Expression *edx = e->diff("x");
    ASSERT_EQ(edx->get_str(), "((1)*(5)-(x)*(0))/((5)*(5))"); // (1*5-x*0)/(5*5)

    delete e;
    delete edx;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
