#include "compiler-factory.hpp"

std::map<std::string, Language> LanguageMapper::extension_map = {
    {".cpp", Language::Cxx},
    {".cc",  Language::Cxx},
    {".hpp", Language::Cxx},
    {".h",   Language::Cxx},
    {".py",  Language::Python}
};