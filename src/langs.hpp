#pragma once

#include "utils/compiler-factory.hpp"
#include "utils/parser.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

enum class Language {
    Cxx,
    Python
};

class LanguageMapper {
public:
    Language FromExtension(const std::string& extension) const {
        const auto it = extension_map.find(extension);
        if (it == extension_map.end()) {
            throw std::out_of_range("Language is not supported now, bad extension: " + extension);
        }
        return it->second;
    }
private:
    const std::map<std::string, Language> extension_map = {
        {".cpp", Language::Cxx},
        {".py", Language::Python}
    };
};

class CompilerFactory {
public:
    static std::unique_ptr<LanguageCompiler> FromPath(const std::string& file_path) {
        const auto& ext = Parser::GetExtension(file_path);

        LanguageMapper language_mapper;
        auto lang = language_mapper.FromExtension(ext);
        switch (lang) {
        case Language::Cxx: 
            return std::make_unique<CppCompiler>();
        case Language::Python: 
            return std::make_unique<PyCompiler>();
        }
    }
};