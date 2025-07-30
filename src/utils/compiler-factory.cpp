#include "compiler-factory.hpp"

bool CppCompiler::Compile(const std::string& file_path,
                const std::string& bin_path) const {
    std::string cmd = "clang++ -std=c++20 " + file_path + " -o " + bin_path;
    return system(cmd.c_str()) == 0;
}

bool PyCompiler::Compile(const std::string& file_path,
                const std::string& bin_path) const {
    std::string cmd = "echo '#!/bin/bash' > " + bin_path + " && "
            "echo 'python3 " + file_path + " \"$@\"' >> " + bin_path + " && "
            "chmod +x " + bin_path;
    return system(cmd.c_str()) == 0;
}