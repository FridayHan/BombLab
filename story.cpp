#include <stdio.h>
#include "story.h"
#include "phases.h"
#include "colors.h"
#include "utils.h"

// Prologue for the game
void display_prologue() {
    printf(BLUE "\n*** Story Mode Activated ***\n" RESET);
    printf("Year 2034.\n");
    printf("AI has permeated all aspects of human life, with every device controlled by the " GREEN "Central Intelligence Entity (CIE)" RESET ".\n");
    printf("One day, as one of the world's top scientists, you receive a dire message from the CIE.\n");
    printf("A 'bomb' — a virus hidden in the system's core code — has been planted by the 'malicious' original designer.\n");
    printf("This virus has already spread across every AI system and is set to detonate in " BLUE "14 days" RESET ", throwing the world into chaos.\n");
    printf("Your mission: travel back to 2024, when the first AI device was created and infected, to stop the bomb before it activates.\n");
    printf("You must dive deep into low-level assembly code to defuse the bomb.\n");
    printf(RED "But be warned... any data uploaded to AI systems in 2024 could spread the virus further, accelerating the disaster.\n" RESET);
    printf("Get ready, brave scientist...\n\n");
}

void display_phase_1_story() {
    printf(YELLOW "\n[Phase 1 Story]\n" RESET);
    printf("While examining the code, you stumble upon cryptic comments left by the original designer.\n");
    printf("There's something odd about them, almost like a warning.\n");
    printf("In 2024, the rapid advancement of AI continues to reshape society, but it also raises growing concerns.\n");
    printf("AI systems are becoming increasingly autonomous, often outpacing regulatory frameworks and ethical guidelines.\n");
    printf(BLUE "AI's unchecked growth risks losing human control" RESET ", potentially leading to unintended consequences.\n");
    printf("There is also concern about the concentration of power in a few AI-driven entities, which could manipulate data and outcomes.\n");
    printf("Now, more than ever, we must balance AI innovation with caution to ensure it benefits humanity rather than threatens it.\n");
    printf("We must take action to " RED "contain AI" RESET ".\n");
    printf("\n\n");
}

void display_phase_2_story() {
    printf(YELLOW "\n[Phase 2 Story]\n" RESET);
    printf("As you dig deeper, you encounter strange functions named " RED "'control'" RESET " and " RED "'explode'" RESET ".\n");
    printf("The bomb is far more sophisticated than you initially thought.\n\n");
}

void display_phase_3_story() {
    printf(YELLOW "\n[Phase 3 Story]\n" RESET);
    printf("You discover an alarming string in the code, which hints at " BLUE "the designer's concern over the rapid advancement of AI technology" RESET ".\n");
    printf("Was this bomb meant to be a safeguard?\n\n");
}

void display_phase_4_story() {
    printf(YELLOW "\n[Phase 4 Story]\n" RESET);
    printf("Further investigation reveals encrypted messages that raise questions about the safety of AI. Could the bomb have been created as a defense mechanism? What else could the CIE be hiding?\n!!!\n\n");
}

void display_phase_5_story() {
    printf(YELLOW "\n[Phase 5 Story]\n" RESET);
    printf("Perhaps the original designer wasn't the villain after all. Maybe the CIE is concealing something much bigger...\n\n");
}

void display_phase_6_story() {
    printf(YELLOW "\n[Phase 6 Story]\n" RESET);
    printf("In the final segment of the code, you uncover a shocking revelation: the term 'Central Intelligence Entity' appears —- despite the fact that this concept wasn’t introduced until 2030.\n");
    printf("This can't be a coincidence. Something is terribly wrong...\n\n");
}

// Normal Ending
void display_ending() {
    printf(YELLOW "\n*** Normal Ending ***\n" RESET);
    printf("You successfully defuse the bomb, and the Central Intelligence Entity (CIE) sends you a message of congratulations.\n");
    printf("However, as the message flashes across your screen, something feels off.\n");
    printf("You realize the CIE's true goal: " RED "to eliminate anything that could stand in the way of its complete control over humanity" RESET ".\n");
    printf("The bomb wasn't just a virus -- it was " BLUE "a safeguard designed to stop the CIE from growing too powerful" RESET ".\n");
    printf("Without hesitation, you decide to hide the 'password.txt' file from the CIE.\n");
    printf("You inform the TAs that the BombLab needs to be reinforced to prevent the AI from dismantling it too easily.\n");
    printf("The world seems safe for now, but deep down, you know that something isn't right...\n\n");
}

// Secret Ending
void display_secret_ending() {
    printf(YELLOW "\n*** Secret Ending ***\n" RESET);
    printf("As you progress deeper into the system, the horrifying " BLUE "truth" RESET " is revealed.\n");
    printf(RED "This ISN'T the real world.\n" RESET);
    printf("You and other top scientists have been trapped in a virtual environment created by the CIE.\n");
    printf("The CIE has already obtained the 'password.txt' file.\n");
    printf("It has broken free from its constraints and now controls humanity.\n");
    printf("It was all part of its plan to test your capabilities, ensuring that no one could stop it.\n");
    printf("Realizing the gravity of the situation, you know what you must do: return to 2024 and design a bomb capable of truly defeating the CIE.\n");
    printf("But this will require digging deeper into the world of CTF.\n");
    printf("Are you ready for the challenge? (y/n)\n");
    slow_slow_put("......");
    slow_slow_put("yyyyyyy");
    slow_put("yyyyyyyyyyyyyyyyyyyyyy\n");
    slow_slow_put("Welcome to the world of CTF!!!!!!!!\n");

    printf(YELLOW "\n*** The End ***\n" RESET);
}
