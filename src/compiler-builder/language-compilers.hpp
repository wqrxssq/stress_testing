#pragma once

#include <string>

class LanguageCompiler {
   public:
    virtual ~LanguageCompiler() = default;
    // Compile "file_path" to "bin_path" or create bash-script in "bin_path"
    virtual bool Compile(const std::string& file_path, const std::string& bin_path) const = 0;
};

class CppCompiler final : public LanguageCompiler {
   public:
    bool Compile(const std::string& file_path, const std::string& bin_path) const override;
};

class PyCompiler final : public LanguageCompiler {
   public:
    // create bash-script, to run .py file
    bool Compile(const std::string& file_path, const std::string& bin_path) const override;
};

class CCompiler final : public LanguageCompiler {
   public:
    bool Compile(const std::string& file_path, const std::string& bin_path) const override;
};

class GoCompiler final : public LanguageCompiler {
   public:
    bool Compile(const std::string& file_path, const std::string& bin_path) const override;
};
