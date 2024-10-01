/*
 *  FDU's Bomb+, Version 3.4
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
    for (i = 0; i <= 50; i++) {
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
    char input[50];
    long secret_key = 0;
    char mode_choice = 0;

    printf("Would you like to play in Story Mode? (y/n): ");
    mode_choice = getchar();
    getchar();
    if (mode_choice == 'y' || mode_choice == 'Y')
        mode_choice = 1;
    else
        mode_choice = 0;
    if (mode_choice)
        display_prologue();


    printf("\033[34mYou have 6 phases with which to blow yourself up. Have a nice day!\n\033[0m");


    read_line(input);
    phase_1(input);
    if (mode_choice)
        display_phase_1_story();
    printf("%ld", secret_key);
    puts("\033[34mPhase 1 defused. How about the next one?\033[0m");


    read_line(input);
    phase_2(input);
    puts("\033[34mThat's number 2. Keep going!\033[0m");
    // if (mode_choice)
    //     display_phase_2_story();


    read_line(input);
    phase_3(input);
    puts("\033[34mHalfway there!\033[0m");
    // if (mode_choice)
    //     display_phase_3_story();

    read_line(input);
    phase_4(input);
    puts("\033[34mSo you got that one. Try this one.\033[0m");
    if (mode_choice)
        display_phase_4_story();


    read_line(input);
    phase_5(input);
    puts("\033[34mGood work! On to the next...\033[0m");
    if (mode_choice)
        display_phase_5_story();


    read_line(input);
    phase_6(input);
    puts("\033[34mCool! your skill on Reverse Engineer is great.\033[0m");
    if (mode_choice)
        display_phase_6_story();


    puts("\033[34mCongratulations!\n\033[0m");



    if (secret_key) {
        slow_put("\033[34mWelcome to the secret phase of Bomb+!\n\033[0m");
        slow_put("It is called");
        slow_slow_put("... THE STEINS;GATE\n");

        read_line(input);
        secret_phase(input);

        puts("You are really a Master of Reverse Engineer!");
        true_ending();
    }

    return 0;
}
