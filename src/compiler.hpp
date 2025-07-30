#pragma once

#include <string>

class LanguageCompiler {
public:
    virtual ~LanguageCompiler() = default;
    // Compile "file_path" to "bin_path" or create bash-script in "bin_path"
    virtual bool Compile(const std::string& file_path,
                         const std::string& bin_path) const = 0;
};