#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/detector/compiler-factory.hpp"

TEST(TestLanguageMapper, TestCppExtension) {
    std::string ext = ".cpp";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::Cxx);

    std::string path = "/bar/foo/checker.cpp";
    EXPECT_EQ(LanguageMapper::FromPath(path), Language::Cxx);
}

TEST(TestLanguageMapper, TestPyExtension) {
    std::string ext = ".py";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::Python);

    std::string path = "/bar/foo/generator.py";
    EXPECT_EQ(LanguageMapper::FromPath(path), Language::Python);
}

TEST(TestLanguageMapper, TestCExtension) {
    std::string ext = ".c";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::C);

    std::string path = "/bar/foo/generator.c";
    EXPECT_EQ(LanguageMapper::FromPath(path), Language::C);
}

TEST(TestLanguageMapper, TestGoExtension) {
    std::string ext = ".go";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::Go);

    std::string path = "/bar/foo/generator.go";
    EXPECT_EQ(LanguageMapper::FromPath(path), Language::Go);
}

TEST(TestLanguageMapper, TestWrongExtension) {
    std::string ext = ".md";
    EXPECT_THROW(LanguageMapper::FromExtension(ext), std::out_of_range);

    std::string path = "/bar/foo/checker.md";
    EXPECT_THROW(LanguageMapper::FromExtension(path), std::out_of_range);
}

TEST(TestLanguageMapper, TestEmptyExtension) {
    std::string ext = "";
    EXPECT_THROW(LanguageMapper::FromExtension(ext), std::out_of_range);

    std::string path = "/bar/foo/checker";
    EXPECT_THROW(LanguageMapper::FromExtension(path), std::out_of_range);
}
