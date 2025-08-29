#include <gtest/gtest.h>

#include "../src/utils/parser.hpp"

TEST(TestGetExtension, TestSimpleExtension) {
    std::string path = "/foo/bar.txt";
    EXPECT_EQ(Parser::GetExtension(path), ".txt");
}

TEST(TestGetExtension, TestEmptyExtension) {
    std::string path = "/foo/bar";
    EXPECT_EQ(Parser::GetExtension(path), "");
}

TEST(TestGetExtension, TestHardExtension) {
    std::string path = "/foo/../dummy/bar.cpp";
    EXPECT_EQ(Parser::GetExtension(path), ".cpp");
}

TEST(TestGetExtension, TestRelativePathExtension) {
    std::string path = "../dummy/bar.py";
    EXPECT_EQ(Parser::GetExtension(path), ".py");
}
