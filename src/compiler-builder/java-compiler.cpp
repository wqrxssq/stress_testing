#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>
#include "language-compilers.hpp"

bool JavaCompiler::Compile(const std::string& file_path, const std::string& bin_path) const {
    namespace fs = std::filesystem;
    fs::create_directories(fs::path(bin_path).parent_path());
    auto classes = (fs::path(bin_path).parent_path() / "java_classes").string();
    
    // Extract class name from Java file
    std::string maincls;
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line)) {
        // Look for "class ClassName" or "public class ClassName"
        size_t pos = line.find("class ");
        if (pos != std::string::npos) {
            pos += 6; // Skip "class "
            size_t end = line.find_first_of(" {", pos);
            if (end != std::string::npos) {
                maincls = line.substr(pos, end - pos);
                break;
            }
        }
    }
    file.close();
    
    if (maincls.empty()) {
        return false; // Could not find class name
    }

    std::string cmd =
        "mkdir -p \"" + classes + "\" && "
        "javac -d \"" + classes + "\" \"" + file_path + "\" && "
        "printf '%s\n' '#!/usr/bin/env bash' "
        "'exec java -cp \"" + classes + "\" " + maincls + " \"$@\"' > \"" + bin_path + "\" && "
        "chmod +x \"" + bin_path + "\"";

    return std::system(cmd.c_str()) == 0;
}
