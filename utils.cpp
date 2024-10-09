#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include "utils.h"

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
            // 去除行尾的注释
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }

            // 如果行为空或去掉注释后为空，跳过该行
            if (line.empty()) continue;

            size_t delimiterPos = line.find("=");
            if (delimiterPos == std::string::npos) continue;  // 如果没有找到等号，跳过该行

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // 去除 key 和 value 两端的空白字符
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if (key == "test_phase") {
                std::stringstream ss(value);
                std::string item;
                while (std::getline(ss, item, ',')) {
                    item.erase(0, item.find_first_not_of(" \t"));
                    item.erase(item.find_last_not_of(" \t") + 1);
                    int phase = std::stoi(item);
                    testPhases.push_back(phase);  // 将 test_phase 字符串解析为整数列表
                }

                // 检查 testPhases 是否是1-6的子集，且顺序递增，最多6个
                if (testPhases.size() > 6) {
                    printf("Error: test_phase contains more than 6 phases.\n");
                    return std::make_pair(config, std::vector<int>{});  // 返回空的 testPhases 表示错误
                }

                for (unsigned long i = 0; i < testPhases.size(); ++i) {
                    if (testPhases[i] < 1 || testPhases[i] > 6) {
                        printf("Error: test_phase contains invalid phase number: %d. Valid range is 1 to 6.\n", testPhases[i]);
                        return std::make_pair(config, std::vector<int>{});  // 返回空的 testPhases 表示错误
                    }
                    if (i > 0 && testPhases[i] <= testPhases[i - 1]) {
                        printf("Error: test_phase is not in strictly increasing order.\n");
                        return std::make_pair(config, std::vector<int>{});  // 返回空的 testPhases 表示错误
                    }
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
