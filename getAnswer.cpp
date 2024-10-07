#include <stdio.h>
#include <iostream>
#include <map>
#include <fstream>
#include "utils.h"
#include "phases.h"

void get_1_answer() {
    phase_1_offset = 215 - abs(ID_hash % 10);
    char* answer = phase_1_str + phase_1_offset;
    printf("%s\n", answer);
}

void get_2_answer() {
    int base_add = ID_hash % 4 + 1;
    int ans2[6] = {1};
    for (int h = 1; h < 6; ++h)
        ans2[h] = ans2[h-1] * (-10) + base_add;
    for (int i = 0; i < 6; ++i)
        printf("%d ", ans2[i]);
    printf("\n");
}

void get_5_answer() {
    printf("growth 2034 %x\n", ID_hash % 100);
}

int main() {
    // configure
    std::map<std::string, std::string> config = readConfig("config.txt");
    int jumpMode = std::stoi(config["jump_mode"]);
    bool storyMode = (config["story_mode"] == "true");
    std::string studentID = config["student_id"];
    phase_0(studentID);
    printf("%d\n", ID_hash);
    printf("phase_1 answer: \n");
    get_1_answer();
    printf("phase_2 answer: \n");
    get_2_answer();
    printf("phase_3 answer: \n");
    printf("1 1 o\n");
    printf("phase_4 answer: \n");
    printf("42949672961\n");
    printf("phase_5 answer: \n");
    get_5_answer();
    printf("phase_6 answer: \n");
    printf("4 4 4 4 4 4\n");
}