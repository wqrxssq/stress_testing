#include "language-compilers.hpp"

#include <string>
#include <cstdlib>

bool CppCompiler::Compile(const std::string& file_path,
                const std::string& bin_path) const {
    std::string cmd = "clang++ -std=c++20 " + file_path + " -o " + bin_path;
    return system(cmd.c_str()) == 0;
}