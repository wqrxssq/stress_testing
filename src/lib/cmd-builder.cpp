#include "cmd-builder.hpp"
#include "parser.hpp"

std::string CommandBuilder::BuildCommand(
    const std::string& path_to_file,
    const std::string& path_to_bin
) {
    auto lang =  LangDetector::DetectLang(path_to_file);
    switch (lang) {
        case Lang::Cxx:
            // real compilation
            return "clang++ -std=c++2a " + path_to_file +
                   " -o " + path_to_bin;
        case Lang::Python:
            // create bash-script, to run .py file
            return
                "echo '#!/bin/bash' > " + path_to_bin + " && "
                "echo 'python3 " + path_to_file + " \"$@\"' >> " + path_to_bin + " && "
                "chmod +x " + path_to_bin;
        default:
            throw std::invalid_argument("Unsupported language");
    }
}