#include "config_service.h"

#include <iostream>
#include <fstream>
#include <sstream>


bool parseConfig(const std::string& filename, Config& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "icon") {
            if (std::getline(file, config.icon)) {
                continue;
            }
        } else if (line == "size") {
            if (std::getline(file, line)) {
                std::istringstream iss(line);
                if (!(iss >> config.size_height >> config.size_width)) {
                    std::cerr << "Error: Invalid size format in config file." << std::endl;
                    return false;
                }
            }
        }
    }

    file.close();
    return true;
}

