#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/detector/compiler-factory.hpp"

TEST(TestLanguageMapper, TestCppExtension) {
    std::string ext = ".cpp";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::Cxx);
}

TEST(TestLanguageMapper, TestPyExtension) {
    std::string ext = ".py";
    EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::Python);
}

TEST(TestLanguageMapper, TestWrongExtension) {
    std::string ext = ".js";
    EXPECT_THROW(LanguageMapper::FromExtension(ext), std::out_of_range);
}
