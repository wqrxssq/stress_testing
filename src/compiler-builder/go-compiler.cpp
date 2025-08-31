#include <cstdlib>
#include <string>

#include "language-compilers.hpp"

bool GoCompiler::Compile(const std::string& file_path, const std::string& bin_path) const {
    std::string cmd = "go build -o " + bin_path + " " + file_path;
    return system(cmd.c_str()) == 0;
}
