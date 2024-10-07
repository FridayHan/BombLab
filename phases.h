#ifndef PHASES_H
#define PHASES_H
#include <string>

extern unsigned int ID_hash;
extern char phase_1_str[767];
extern int phase_1_offset;

extern "C" void phase_0(std::string input);
extern "C" void phase_1(char *input);
extern "C" void phase_2(char *input);
extern "C" void phase_3(char *input);
extern "C" void phase_4(char *input);
extern "C" void phase_5(char *input);
extern "C" void phase_6(char *input);
extern "C" void secret_phase(char *input);

#endif // PHASES_H
