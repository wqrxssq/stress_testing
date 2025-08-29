#include "compiler-factory.hpp"

std::unique_ptr<LanguageCompiler> CompilerFactory::FromPath(const std::string& file_path) {
    auto lang = LanguageMapper::FromPath(file_path);

    switch (lang) {
    case Language::Cxx: 
        return std::make_unique<CppCompiler>();
    case Language::Python: 
        return std::make_unique<PyCompiler>();
    }
}