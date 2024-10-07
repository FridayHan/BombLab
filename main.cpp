/*
 *  FDU's Bomb++, Version 3.4
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
#include "utils.h"
#include "phases.h"
#include "story.h"

/*
 * Note to self: Remember to erase this file so my victims will have
 * no idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion.
 */

void read_line(char* input)
{
    char ch;
    int i;
    for (i = 0; i <= 120; i++) {
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
    char input[120];
    long secret_key = 0;
    printf("input address: %p\n", (void*)&input);
    printf("secret_key address: %p\n", (void*)&secret_key);

    // configure
    std::map<std::string, std::string> config = readConfig("config.txt");
    int jumpMode = std::stoi(config["jump_mode"]);
    bool storyMode = (config["story_mode"] == "true");
    std::string studentID = config["student_id"];

    // initialize
    printf("\033[34mPlease enter your Student ID (23307xxxxxx) in the config.txt file.\n"
       "Note: Different Student IDs will generate different answers. Therefore, do not attempt to use someone else's ID for the answers.\033[0m\n");
    phase_0(studentID);
    if (storyMode)
        display_prologue();
    printf("\033[34mYou have 6 phases with which to blow yourself up. Have a nice day!\033[0m\n");

    switch (jumpMode)
    {
        case 1:
            puts("\033[34mPHASE 1...\033[0m");
            read_line(input);
            phase_1(input);
            if (storyMode)
                display_phase_1_story();
            puts("\033[34mPhase 1 defused. How about the next one?\033[0m");

        case 2:
            puts("\033[34mPHASE 2...\033[0m");
            read_line(input);
            phase_2(input);
            puts("\033[34mThat's number 2. Keep going!\033[0m");
            // if (storyMode)
            //     display_phase_2_story();

        case 3:
            puts("\033[34mPHASE 3...\033[0m");
            read_line(input);
            phase_3(input);
            puts("\033[34mHalfway there!\033[0m");
            // if (storyMode)
            //     display_phase_3_story();

        case 4:
            puts("\033[34mPHASE 4...\033[0m");
            read_line(input);
            phase_4(input);
            puts("\033[34mSo you got that one. Try this one.\033[0m");
            if (storyMode)
                display_phase_4_story();

        case 5:
            puts("\033[34mPHASE 5...\033[0m");
            read_line(input);
            phase_5(input);
            puts("\033[34mGood work! On to the next...\033[0m");
            if (storyMode)
                display_phase_5_story();

        case 6:
            puts("\033[34mPHASE 6...\033[0m");
            read_line(input);
            phase_6(input);
            puts("\033[34mCool! your skill on Reverse Engineer is great.\033[0m");
            if (storyMode)
                display_phase_6_story();
            break;

        default:
            printf("\033[31mInvalid jump mode! Please set jump_mode between 1 and 6.\033[0m\n");
            exit(1);
    }

    if (jumpMode == 1)
        puts("\033[34mCongratulations!\033[0m\n");

    if (secret_key) {
        slow_put("\033[34mWelcome to the secret phase of Bomb++!\033[0m\n");
        slow_put("It is called");
        slow_slow_put("... THE STEINS;GATE\n");

        read_line(input);
        secret_phase(input);

        puts("You are really a Master of Reverse Engineer!");
        true_ending();
    }

    return 0;
}
