#include "parser.hpp"
#include <filesystem>

namespace Parser {

std::string GetExtension(const std::string& file_path) {
    std::filesystem::path p(file_path);
    return p.extension().string();
}

} // namepsace Parser