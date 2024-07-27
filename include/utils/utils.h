#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <filesystem>



std::filesystem::path findProjectRoot(const std::string& project_name) {
    std::filesystem::path current_path = std::filesystem::current_path();
    while (current_path.has_parent_path()) {
        if (current_path.filename() == project_name) {
            return current_path;
        }
        current_path = current_path.parent_path();
    }
    throw std::runtime_error("Project root not found");
}


#endif