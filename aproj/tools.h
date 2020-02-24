#pragma once

#include <string>

namespace tools {
    static std::string parse_file_extension(const std::string path)
    {
        std::string extension;
        std::size_t last_slash_pos = path.find_last_of("/");
        std::size_t last_dot_pos = path.find_last_of(".");

        if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
            extension = path.substr(last_dot_pos + 1);
        }

        return extension;
    }
}