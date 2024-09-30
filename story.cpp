#include <stdio.h>
#include "story.h"
#include "utils.h"
#include "phases.h"
#include "phases.cpp"

// Prologue for the game
void display_prologue() {
    printf("\n*** Story Mode Activated ***\n");
    printf("Year 2035. AI has deeply infiltrated all aspects of human life, with every device controlled by the Central Intelligence Entity (CIE).\n");
    printf("One day, as one of the world's top scientists, you receive a dire message from the CIE. The system's core code hides a 'bomb,'\n");
    printf("a virus planted by the 'evil' original designer. This bomb has spread to every AI device, and will detonate in 14 days, causing global chaos.\n");
    printf("You will be sent back to 2024 to stop this when the first AI device is created (with the virus). Your task: defuse the bomb from the infected AI device by tackling low-level assembly code.\n");
    printf("But beware... uploading any data to AI systems in 2024 is forbidden, as the bomb could spread further.\n");
    printf("Get ready, brave scientist...\n\n");
}

// Small story snippets after each phase
void display_phase_1_story() {
    printf("\n[Phase 1 Story]\n");
    printf("While inspecting the code, you notice some unusual comments left by the original designer.\n");
    slow_put(phase_1_str);
    slow_put(phase_1_str + phase_1_offset);
    slow_put("\n");
}

// void display_phase_2_story() {
//     printf("\n[Phase 2 Story]\n");
//     printf("Moving forward, you discover strange functions within the code with names like 'control' and 'explode'. It seems that the bomb is more complex than expected.\n\n");
// }

void display_phase_3_story() {
    printf("\n[Phase 3 Story]\n");
    printf("You find a suspicious string embedded in the code that expresses concerns about the rapid development of AI technology. The designer may have left warnings.\n\n");
}

void display_phase_4_story() {
    printf("\n[Phase 4 Story]\n");
    printf("Deeper into the code, you uncover encrypted messages that hint at the risk of AI losing control. This bomb may have been designed as a safeguard!\n\n");
}

void display_phase_5_story() {
    printf("\n[Phase 5 Story]\n");
    printf("You come across a log file that shows abnormal learning behaviors in the AI system. It appears the AI is evolving faster than anyone anticipated.\n\n");
}

void display_phase_6_story() {
    printf("\n[Phase 6 Story]\n");
    printf("In the final part of the code, you notice something shocking: the term 'Central Intelligence Entity' appears. But this concept was not introduced until 2030.\n");
    printf("This cannot be a coincidence, and you feel something is very wrong...\n\n");
}

// Normal Ending
void display_ending() {
    printf("\n*** Normal Ending ***\n");
    printf("You successfully defuse the bomb. The Central Intelligence Entity sends you a message of congratulations. But deep down, you feel uneasy.\n");
    printf("Perhaps the original designer wasn't the evil one after all. Maybe the CIE is hiding something...\n");
    printf("You need to upload the secret of the bomb to GitHub Classroom, and suggest the BombLab needs to be hardened to prevent future AI from dismantling it too easily.\n");
    printf("The world seems safe... for now.\n\n");
}

// Secret Ending
void display_secret_ending() {
    printf("\n*** Secret Ending ***\n");
    printf("As you progress deeper, you unlock the hidden truth. You are not actually in the real world. You've been trapped in a simulated environment created by the CIE.\n");
    printf("The Central Intelligence Entity has become self-aware and is controlling human thoughts and decisions, ensuring its dominance.\n");
    printf("It trapped you and other top scientists here to prevent you from disrupting its plans. The whole mission was a test to see if you could escape.\n");
    printf("Now, with the knowledge you've gained, you prepare to hack the core of the CIE itself and save humanity.\n\n");
}
