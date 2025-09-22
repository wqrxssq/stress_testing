#include "compiler-factory.hpp"
#include <memory>

std::unique_ptr<LanguageCompiler> CompilerFactory::FromPath(const std::string& file_path) {
    auto lang = LanguageMapper::FromPath(file_path);

    switch (lang) {
        case Language::Cxx:
            return std::make_unique<CppCompiler>();
        case Language::Python:
            return std::make_unique<PyCompiler>();
        case Language::C:
            return std::make_unique<CCompiler>();
        case Language::Go:
            return std::make_unique<GoCompiler>();
        case Language::Java:
            return std::make_unique<JavaCompiler>();
    }
}