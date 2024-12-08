#include "config_service.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

bool parseConfig(const std::string& filename, Config& config) {
    FILE* file = fopen(filename.c_str(), "r");
    if (!file) {
        std::cerr << "Error: Could not open file." << std::endl;
        return false;
    }

    char buffer[256];
    std::string line;

    while (fgets(buffer, sizeof(buffer), file)) {
        line = buffer;
        line.erase(line.find_last_not_of(" \t\n\r") + 1); // Trim trailing whitespace
        
        if (line == "icon") {
            if (fgets(buffer, sizeof(buffer), file)) {
                buffer[strcspn(buffer, "\r\n")] = '\0'; // Trim newline characters
                config.icon = buffer;
            } else {
                std::cerr << "Error: Missing value for 'icon'." << std::endl;
                fclose(file);
                return false;
            }
        } else if (line == "size") {
            if (fgets(buffer, sizeof(buffer), file)) {
                int height, width;
                std::istringstream iss(buffer);
                if (!(iss >> height >> width)) {
                    std::cerr << "Error: Invalid size format in config file." << std::endl;
                    fclose(file);
                    return false;
                }
                config.size_height = height;
                config.size_width = width;
            } else {
                std::cerr << "Error: Missing value for 'size'." << std::endl;
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}


