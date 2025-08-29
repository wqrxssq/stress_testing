#pragma once

#include "../compiler-builder/language-compilers.hpp"
#include "../langs.hpp"

#include <map>

class LanguageMapper {
public:
    ~LanguageMapper() = default;

    static Language FromExtension(const std::string& extension);
    static Language FromPath(const std::string& path);
protected:
    static std::map<std::string, Language> extension_map;
};

namespace CompilerFactory {
    std::unique_ptr<LanguageCompiler> FromPath(const std::string& file_path);
} // namespace CompilerFactory