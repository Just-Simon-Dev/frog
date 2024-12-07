//
// Created by simon on 07.12.24.
//

#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

struct Config {
    char *icon;
    int size_height;
    int size_width;
};

void initConfig(Config *config);

bool loadConfig(const char* filename, Config* config);

const char *getConfigValue(const char *key, Config *config);

#endif //CONFIG_SERVICE_H
