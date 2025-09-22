#include <gtest/gtest.h>
#include "../src/detector/compiler-factory.hpp"

TEST(TestCompilerFactory, TestCppPath) {
    std::string path_to_file = "src/cpp-runner/generator.cpp";
    auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
    auto& compiler = *compiler_ptr;
    EXPECT_EQ(typeid(compiler), typeid(CppCompiler));
}

TEST(TestCompilerFactory, TestPyPath) {
    std::string path_to_file = "src/py-runner/generator.py";
    auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
    auto& compiler = *compiler_ptr;
    EXPECT_EQ(typeid(compiler), typeid(PyCompiler));
}

TEST(TestCompilerFactory, TestCPath) {
    std::string path_to_file = "src/cpp-runner/generator.c";
    auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
    auto& compiler = *compiler_ptr;
    EXPECT_EQ(typeid(compiler), typeid(CCompiler));
}

TEST(TestCompilerFactory, TestGoPath) {
    std::string path_to_file = "src/cpp-runner/generator.go";
    auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
    auto& compiler = *compiler_ptr;
    EXPECT_EQ(typeid(compiler), typeid(GoCompiler));
}

TEST(TestCompilerFactory, TestJavaPath) {
    std::string path_to_file = "src/java-runner/generator.java";
    auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
    auto& compiler = *compiler_ptr;
    EXPECT_EQ(typeid(compiler), typeid(JavaCompiler));
}

TEST(TestCompilerFactory, TestBadPath) {
    std::string path_to_file = "dummy.txt";
    EXPECT_ANY_THROW(CompilerFactory::FromPath(path_to_file));
}
