#include "IO.hpp"
#include "bufferedIO.hpp"

#include <gmock/gmock.h>
#include <filesystem>
#include <gtest/gtest.h>

TEST(StringIO, ReadFullStr){
    stringIO rw("aga");
    ASSERT_EQ(rw.readString(), "aga");
    ASSERT_EQ(rw.get_cur_pos(), 0);
}

TEST(StringIO, IsOpen) {
    stringIO rw("");
    ASSERT_TRUE(rw.isOpen());
}

TEST(StringIO, IsNotOpen) {
    stringIO rw("");
    rw.close();
    ASSERT_FALSE(rw.isOpen());
}

TEST(StringIO, IsNotEof) {
    stringIO rw("abc");
    ASSERT_FALSE(rw.isEof());
}

TEST(StringIO, ReadChar) {
    stringIO rw("abc");
    ASSERT_EQ(rw.readChar(), 'c');
    ASSERT_EQ(rw.readChar(), 'b');
    ASSERT_EQ(rw.readChar(), 'a');
    ASSERT_EQ(rw.readChar(), '\0');
}

TEST(StringIO, ReadInt) {
    stringIO rw("12345");
    ASSERT_EQ(rw.readInt(), 12345);
}

TEST(StringIO, ReadString) {
    stringIO rw("abc");
    ASSERT_EQ(rw.readString(), "abc");
}

TEST(StringIO, ReadStringLen) {
    stringIO rw("abcdef");
    ASSERT_EQ(rw.readString(3), "def");
}

TEST(StringIO, WriteChar) {
    stringIO rw("some string");
    rw.write('a');
    ASSERT_EQ(rw.readChar(), 'a');
}

TEST(StringIO, WriteInt) {
    stringIO rw("");
    rw.write(12345);
    ASSERT_EQ(rw.readString(), "12345");
}

TEST(StringIO, WriteString) {
    stringIO rw("");
    rw.write("abc");
    ASSERT_EQ(rw.readString(), "abc");
}

TEST(FileIO, WriteChar) {
    fileIO rw("../../task8/test.txt");
    rw.write('a');
    ASSERT_EQ(rw.readChar(), 'a');
}

TEST(FileIO, WriteInt) {
    fileIO rw("../../task8/test.txt");
    rw.write(12345);
    ASSERT_EQ(rw.readString(), "12345");
}

TEST(FileIO, WriteString) {
    fileIO rw("../../task8/test.txt");
    rw.write("abc");
    ASSERT_EQ(rw.readString(), "abc");
}

TEST(FileIO, WriteStringLen) {
    fileIO rw("../../task8/test.txt");
    rw.write("abcd");
    ASSERT_EQ(rw.readString(3), "bcd");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
