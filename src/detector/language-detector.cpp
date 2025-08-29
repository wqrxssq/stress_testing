#include "compiler-factory.hpp"
#include "../utils/parser.hpp"

Language LanguageMapper::FromExtension(const std::string& extension) {
    const auto it = extension_map.find(extension);
    if (it == extension_map.end()) {
        throw std::out_of_range("Language is not supported now, bad extension: " + extension);
    }
    return it->second;
}

Language LanguageMapper::FromPath(const std::string& path) {
    const auto& ext = Parser::GetExtension(path);
    return LanguageMapper::FromExtension(ext);
}