#pragma once

#include <string>

class CommandBuilder {
public:
    // Generates a command or script for the specified language
    static std::string BuildCommand(
        const std::string& path_to_file,
        const std::string& path_to_bin
    );
};
