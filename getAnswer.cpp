#include <stdio.h>
#include <map>
#include "utils.h"
#include "phases.h"

void get_1_answer() {
    phase_1_offset = 215 - ID_hash % 10;
    char* answer = phase_1_str + phase_1_offset;
    printf("%s", answer);
    for (int i = 0; i < 80; ++i)
        printf(" ");
    printf("\n");
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

void get_3_answer() {
    int check = ID_hash % 8;
    switch(check)
    {
        case 0:
            printf("1 1 o\n");
            break;
        case 1:
            printf("2 3 v\n");
            break;
        case 2:
            printf("5 8 e\n");
            break;
        case 3:
            printf("13 21 r\n");
            break;
        case 4:
            printf("34 55 f\n");
            break;
        case 5:
            printf("89 144 l\n");
            break;
        case 6:
            printf("233 377 o\n");
            break;
        case 7:
            printf("610 987 w\n");
            break;
    }
}

void get_5_answer() {
    printf("growth 2034 %u\n", ID_hash % 0x1000);
}

void get_6_answer_with_secret() {
    printf("4 4 4 4 4 4");
    printf("\n");
}

int main() {
    // configure
    auto [config, testPhases] = readConfig("config.txt"); 
    bool storyMode = (config["story_mode"] == "true");
    std::string studentID = config["student_id"];
    phase_0(studentID);
    // printf("%d\n\n", ID_hash);
    // printf("phase_1 answer: \n");
    get_1_answer();
    // printf("phase_2 answer: \n");
    get_2_answer();
    // printf("phase_3 answer: \n");
    get_3_answer();
    // printf("phase_4 answer: \n");
    printf("42949672961\n");
    // printf("phase_5 answer: \n");
    get_5_answer();
    // printf("phase_6 answer: \n");
    get_6_answer_with_secret();
    // printf("secret_phase answer: \n");
    printf("CIE\n");
}