#include "framework.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(get_x(p), 0.0);
    EXPECT_DOUBLE_EQ(get_y(p), 0.0);
}

TEST(PointTest, ConstructorWithCoordinates) {
    Point p(1.0, 2.0);
    EXPECT_DOUBLE_EQ(get_x(p), 1.0);
    EXPECT_DOUBLE_EQ(get_y(p), 2.0);
}

TEST(LineTest, ConstructorFromTwoPoints) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Line line(p1, p2);
    
    EXPECT_DOUBLE_EQ(get_x(line.start), 1.0);
    EXPECT_DOUBLE_EQ(get_y(line.start), 2.0);
    EXPECT_DOUBLE_EQ(get_x(line.end), 3.0);
    EXPECT_DOUBLE_EQ(get_y(line.end), 4.0);
}

TEST(LineTest, ConstructorFromCoefficients) {
    Line line(2.0, -1.0, 3.0);
    
    EXPECT_DOUBLE_EQ(get_x(line.start), 0.0);
    EXPECT_DOUBLE_EQ(get_y(line.start), 3.0);
    EXPECT_DOUBLE_EQ(get_x(line.end), 1.0);
    EXPECT_DOUBLE_EQ(get_y(line.end), 5.0);
}

TEST(LineTest, FailFindIntersection) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Line line1(p1, p2);
    
    Point p3(2.0, -1.0);
    Point p4(3.0, 0.0);
    Line line2(p3, p4);
    
    try{
        Point intersection = line1.findIntersection(line2);
        FAIL() << "Dont get exception";
    } catch (const std::exception& err) {
        EXPECT_EQ(err.what(), std::string("Lines are parallel, no intersection point!"));
    } catch (...) {
        FAIL() << "Get unexpected exception";
    }
}

TEST(LineTest, PositiveFindIntersection) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 6.0);
    Line line1(p1, p2);
    
    Point p3(0.0, -1.0);
    Point p4(3.0, 2.0);
    Line line2(p3, p4);
    
    Point intersection = line1.findIntersection(line2);

    EXPECT_DOUBLE_EQ(get_x(intersection), -1.0);
    EXPECT_DOUBLE_EQ(get_y(intersection), -2.0);
}

TEST(LineTest, FindPerpendicularLine) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Line line(p1, p2);
    
    Point point(5.0, 6.0);
    Line perpendicularLine = line.findPerpendicularLine(point);
    
    EXPECT_DOUBLE_EQ(get_x(perpendicularLine.start), 0.0);
    EXPECT_DOUBLE_EQ(get_y(perpendicularLine.start), 11.0);
    EXPECT_DOUBLE_EQ(get_x(perpendicularLine.end), 1.0);
    EXPECT_DOUBLE_EQ(get_y(perpendicularLine.end), 10.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
