#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/langs.hpp"

TEST(TestLanguageMapper, TestCppExtension) {
    std::string ext = ".cpp";
    auto lang_mapper = LanguageMapper();
    EXPECT_EQ(lang_mapper.FromExtension(ext), Language::Cxx);
}

TEST(TestLanguageMapper, TestPyExtension) {
    std::string ext = ".py";
    auto lang_mapper = LanguageMapper();
    EXPECT_EQ(lang_mapper.FromExtension(ext), Language::Python);
}

TEST(TestLanguageMapper, TestWrongExtension) {
    std::string ext = ".js";
    auto lang_mapper = LanguageMapper();
    EXPECT_THROW(lang_mapper.FromExtension(ext), std::out_of_range);
}

