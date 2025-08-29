#include <cstdlib>
#include <string>

#include "language-compilers.hpp"

bool CCompiler::Compile(const std::string& file_path, const std::string& bin_path) const {
    std::string cmd = "gcc " + file_path + " -o " + bin_path;
    return system(cmd.c_str()) == 0;
}