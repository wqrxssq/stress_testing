#include "parser.hpp"
#include <stdexcept>

Lang LangDetector::DetectLang(const std::string &file_path) {
    auto pos = file_path.find_last_of('.');
    if (pos == std::string::npos) {
        throw std::invalid_argument("No extension found in file path: " + file_path);
    }
    std::string ext = file_path.substr(pos);
    if (ext == ".cpp") {
        return Lang::Cxx;
    } else if (ext == ".py") {
        return Lang::Python;
    } else {
        throw std::invalid_argument("Unsupported file extension: " + ext);
    }
}