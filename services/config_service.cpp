#include "config_service.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

// Initialize the configuration structure
void initConfig(Config* config) {
    if (config == nullptr) return;
    config->icon = (char *) 'F';
    config->size_height = 1;
    config->size_width = 1;
}

// Load the configuration from a file
bool loadConfig(const char* filename, Config* config) {
    if (filename == nullptr || config == nullptr) return false;

    FILE* file = std::fopen(filename, "r");
    if (file == nullptr) {
        std::perror("Error opening config file");
        return false;
    }

    char line[256];
    while (std::fgets(line, sizeof(line), file)) {
        char key[50], value[50];
        if (std::sscanf(line, "%49s %49[^\n]", key, value) == 2) {
            if (std::strcmp(key, "icon") == 0) {
                config->icon = new char[std::strlen(value) + 1];
                std::strncpy(config->icon, value, sizeof(config->icon) - 1);
            } else if (std::strcmp(key, "size") == 0) {
                std::sscanf(value, "%d %d", &config->size_height, &config->size_width);
            }
        }
    }

    std::fclose(file);
    return true;
}

// Retrieve a configuration value by key as a string
const char* getConfigValue(const char* key, const Config* config) {
    if (key == nullptr || config == nullptr) return nullptr;

    if (std::strcmp(key, "car_icon") == 0) {
        return config->icon;
    } else if (std::strcmp(key, "car_size_height") == 0) {
        static char buffer[12];
        std::sprintf(buffer, "%d", config->size_height);
        return buffer;
    } else if (std::strcmp(key, "car_size_width") == 0) {
        static char buffer[12];
        std::sprintf(buffer, "%d", config->size_width);
        return buffer;
    }
    return nullptr;
}
