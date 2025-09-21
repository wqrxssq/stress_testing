#include "compiler-factory.hpp"

std::map<std::string, Language> LanguageMapper::extension_map = {
    {".cpp", Language::Cxx},
    {".cc",  Language::Cxx},
    {".py",  Language::Python},
    {".c", Language::C},
    {".go", Language::Go},
    {".java", Language::Java}
};