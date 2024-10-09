#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

void explode_bomb() {
    printf("BOOM!!!\n");

    // try open fail.txt
    FILE* fp;
    if ((fp = fopen("fail.txt", "r")) == NULL)
        exit(1);

    while (!feof(fp))
    {
        char ch = fgetc(fp);
        if (ch != EOF)
            putchar(ch);
    }

    fclose(fp);

    exit(1);
}

std::pair<std::map<std::string, std::string>, std::vector<int>> readConfig(const std::string& filename)
{
    std::ifstream configFile(filename);
    std::map<std::string, std::string> config;
    std::vector<int> testPhases;  // 存储解析后的 test_phase 阶段
    std::string line;

    if (configFile.is_open()) {
        while (std::getline(configFile, line)) {
            if (line.empty() || line[0] == '#') continue;

            size_t delimiterPos = line.find("=");
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if (key == "test_phase") {
                std::stringstream ss(value);
                std::string item;
                while (std::getline(ss, item, ',')) {
                    testPhases.push_back(std::stoi(item));  // 将 test_phase 字符串解析为整数列表
                }
            } else {
                config[key] = value;
            }
        }
        configFile.close();
    } else {
        printf("Unable to open config file: %s", filename.c_str());
    }

    return std::make_pair(config, testPhases);  // 返回 config 和 test_phases
}

// put a string to stdout, one character at a time, interval 0.1s
void slow_put(const char* str)
{
    while (*str != '\0')
    {
        putchar(*str);
        str++;

        struct timespec ts;
        ts.tv_sec = 0;
        // ts.tv_nsec = 15000000;
        ts.tv_nsec = 50000000;
        nanosleep(&ts, NULL);

        fflush(stdout);
    }
}

void slow_slow_put(const char* str)
{
    while (*str != '\0')
    {
        putchar(*str);
        str++;

        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 300000000;
        nanosleep(&ts, NULL);

        fflush(stdout);
    }
}

void read_six_numbers(char *buf, int *nums)
{
    int nums_read = sscanf(buf, "%d %d %d %d %d %d", &nums[0], &nums[1],
            &nums[2], &nums[3], &nums[4], &nums[5]);
    if (nums_read != 6 || !nums[0])
        explode_bomb();
}

void true_ending()
{
    puts("You have successfully defused the bomb!");
}
