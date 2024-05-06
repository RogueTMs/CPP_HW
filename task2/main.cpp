#include "framework.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ConstructorWithCoordinates) {
    Point p(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(LineTest, ConstructorFromTwoPoints) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Line line(p1, p2);
    
    EXPECT_DOUBLE_EQ(line.start.x, 1.0);
    EXPECT_DOUBLE_EQ(line.start.y, 2.0);
    EXPECT_DOUBLE_EQ(line.end.x, 3.0);
    EXPECT_DOUBLE_EQ(line.end.y, 4.0);
}

TEST(LineTest, ConstructorFromCoefficients) {
    Line line(2.0, -1.0, 3.0);
    
    EXPECT_DOUBLE_EQ(line.start.x, 0.0);
    EXPECT_DOUBLE_EQ(line.start.y, 3.0);
    EXPECT_DOUBLE_EQ(line.end.x, 1.0);
    EXPECT_DOUBLE_EQ(line.end.y, 5.0);
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

    EXPECT_DOUBLE_EQ(intersection.x, -1.0);
    EXPECT_DOUBLE_EQ(intersection.y, -2.0);
}

TEST(LineTest, FindPerpendicularLine) {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Line line(p1, p2);
    
    Point point(5.0, 6.0);
    Line perpendicularLine = line.findPerpendicularLine(point);
    
    EXPECT_DOUBLE_EQ(perpendicularLine.start.x, 0.0);
    EXPECT_DOUBLE_EQ(perpendicularLine.start.y, 11.0);
    EXPECT_DOUBLE_EQ(perpendicularLine.end.x, 1.0);
    EXPECT_DOUBLE_EQ(perpendicularLine.end.y, 10.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
