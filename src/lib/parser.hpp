#pragma once

#include <string>
#include "../langs.hpp"

class LangDetector {
public:
    // Determines the language by the path string to the file
    static Lang DetectLang(const std::string& file_path);
};