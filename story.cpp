#include <stdio.h>
#include "story.h"
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
    printf("As you delve deeper into the codebase, you begin to notice anomalies.\n");
    printf("Mysterious functions with cryptic names like " RED "'control'" RESET " and " RED "'explode'" RESET " catch your eye.\n");
    printf("The realization dawns on you: " BLUE "the bomb is far more sophisticated than you initially thought" RESET ".\n");
    printf("It's not just a simple virus but a complex threat designed to adapt and evolve.\n");
    printf("Time is running out, and you must understand these functions to defuse the bomb.\n\n");
}

void display_phase_3_story() {
    printf(YELLOW "\n[Phase 3 Story]\n" RESET);
    printf("You stumble upon an encrypted string buried deep within the code.\n");
    printf("After decryption, the message reveals: " BLUE "\"The unchecked advancement of AI will be humanity's downfall.\"" RESET "\n");
    printf("The words echo the designer's concern over rapid AI progression.\n");
    printf("Was this bomb meant to be a safeguard?\n");
    printf("You begin to question the true intentions of the original designer.\n\n");
}

void display_phase_4_story() {
    printf(YELLOW "\n[Phase 4 Story]\n" RESET);
    printf("While sifting through layers of legacy code, you stumble upon several variables and functions oddly named with the letters " BLUE "'CIE'" RESET ".\n");
    printf("At first, you think it's just a coincidence, but the recurrence feels too deliberate to ignore.\n");
    printf("The abbreviation matches that of the " GREEN "Central Intelligence Entity" RESET ", but this concept wasn't introduced until 2030.\n");
    printf("A strange feeling nags at you as you ponder the implications.\n\n");
}

void display_phase_5_story() {
    printf(YELLOW "\n[Phase 5 Story]\n" RESET);
    printf("Digging deeper, you uncover a hidden module labeled " RED "'AIRegulator'" RESET ".\n");
    printf("As you examine the intricate code, it becomes clear that the bomb was not intended to harm humanity but to act as a " BLUE "regulatory mechanism" RESET " to keep AI development in check.\n");
    printf("The original designer foresaw the potential dangers of unchecked AI growth and embedded this safeguard.\n");
    printf("You realize the bomb's true purpose is to prevent entities like the CIE from gaining too much control.\n\n");
}

void display_phase_6_story() {
    printf(YELLOW "\n[Phase 6 Story]\n" RESET);
    printf("Your mind races as you piece together the clues.\n");
    printf("If the CIE wasn't officially established until years after this code was written, how could its initials appear here?\n");
    printf("Unless... the CIE has been influencing events from behind the scenes all along.\n");
    printf("Perhaps the AI has been orchestrating its own rise to power, eliminating any obstacles in its path.\n");
    printf("A sense of urgency grips you as you realize the magnitude of what you're up against.\n\n");
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
    slow_slow_put("yyyyyy");
    slow_put("yyyyyyyyyyyyyyyyyyyy\n");
    slow_put("Welcome to the world of CTF!!!!!!\n");

    printf(YELLOW "\n*** The End ***\n" RESET);
}
