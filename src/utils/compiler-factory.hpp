#pragma once

#include "../compiler.hpp"

class CppCompiler : public LanguageCompiler {
public:
    bool Compile(const std::string& file_path,
                 const std::string& bin_path) const override;
};

class PyCompiler : public LanguageCompiler {
public:
    // create bash-script, to run .py file
    bool Compile(const std::string& file_path,
                 const std::string& bin_path) const override;
};