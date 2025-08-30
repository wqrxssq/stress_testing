#pragma once

#include <map>
#include <memory>

#include "../compiler-builder/language-compilers.hpp"
#include "../langs.hpp"

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
}  // namespace CompilerFactory