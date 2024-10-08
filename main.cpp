/*
 *  FDU's Bomb++, Version 3.6
 *  Copyright 2024, FDU ICS2024. All rights reserved.
 *  
 *  LICENSE:
 *
 *  FDU hereby grants you (the VICTIM) explicit permission to use
 *  this bomb. This is a time limited license, which expires on the
 *  death of the VICTIM.
 *  We take no responsibility for damage, frustration, insanity,
 *  bug-eyes, carpal-tunnel syndrome, loss of sleep, or other harm to
 *  the VICTIM.
 *  This license is null and void where the BOMB is prohibited by law.
 */

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <cstring>
#include "utils.h"
#include "phases.h"
#include "story.h"
#include "colors.h"

/*
 * Note to self: Remember to erase this file so my victims will have
 * no idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion.
 */

void read_line(char* input)
{
    char ch;
    int i;
    for (i = 0; i <= 88; i++) {
        ch = getchar();
        if (ch == '\n') {
            input[i] = '\0';
            return;
        } else {
            input[i] = ch;
        }
    }
    input[i] = '\0';

    while (getchar() != '\n'); // clear the input buffer
}

int main()
{   
    long secret_key = 0;
    char input[88];

    memset(input, 0, sizeof(input));
    memset(&secret_key, 0, sizeof(secret_key));

    // configure
    std::map<std::string, std::string> config = readConfig("config.txt");
    int jumpMode = std::stoi(config["jump_mode"]);
    bool storyMode = (config["story_mode"] == "true");
    std::string studentID = config["student_id"];


    // initialize
    printf(BLUE "Please enter your Student ID (23307xxxxxx) in the config.txt file.\n"
       "Note: Different Student IDs will generate different answers. Therefore, do not attempt to use someone else's ID for the answers." RESET "\n");
    phase_0(studentID);
    if (storyMode)
        display_prologue();
    printf(BLUE "You have 6 phases with which to blow yourself up. Have a nice day!" RESET "\n");

    switch (jumpMode)
    {
        case 1:
            printf(BLUE "PHASE 1..." RESET);
            read_line(input);
            phase_1(input);
            printf(BLUE "Phase 1 defused. How about the next one?" RESET);
            if (storyMode)
                display_phase_1_story();

        case 2:
            printf(BLUE "PHASE 2..." RESET);
            read_line(input);
            phase_2(input);
            printf(BLUE "That's number 2. Keep going!" RESET);
            if (storyMode)
                display_phase_2_story();

        case 3:
            printf(BLUE "PHASE 3..." RESET);
            read_line(input);
            phase_3(input);
            printf(BLUE "Halfway there!" RESET);
            if (storyMode)
                display_phase_3_story();

        case 4:
            printf(BLUE "PHASE 4..." RESET);
            read_line(input);
            phase_4(input);
            printf(BLUE "So you got that one. Try this one." RESET);
            if (storyMode)
                display_phase_4_story();

        case 5:
            printf(BLUE "PHASE 5..." RESET);
            read_line(input);
            phase_5(input);
            printf(BLUE "Good work! On to the next..." RESET);
            if (storyMode)
                display_phase_5_story();

        case 6:
            printf(BLUE "PHASE 6..." RESET);
            read_line(input);
            phase_6(input);
            printf(BLUE "Cool! your skill on Reverse Engineer is great." RESET);
            if (storyMode)
                display_phase_6_story();
            break;

        default:
            printf("\033[31mInvalid jump mode! Please set jump_mode between 1 and 6." RESET "\n");
            exit(1);
    }

    if (jumpMode == 1)
        printf(BLUE "Congratulations!" RESET "\n");

    if (secret_key) {
        slow_put(BLUE "Welcome to the secret phase of Bomb++!" RESET "\n");
        slow_put("It is called");
        slow_slow_put("... THE STEINS;GATE\n");

        read_line(input);
        secret_phase(input);

        printf("You are really a Master of Reverse Engineer!");
        true_ending();
    }

    return 0;
}
