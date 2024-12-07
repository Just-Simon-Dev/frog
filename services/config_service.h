//
// Created by simon on 07.12.24.
//

#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H
#include <string>

struct Config {
    std::string icon;
    int size_height;
    int size_width;
};

bool parseConfig(const std::string& filename, Config& config);

#endif //CONFIG_SERVICE_H
