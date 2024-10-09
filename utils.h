#ifndef UTILS_H
#define UTILS_H
#include <map>
#include <string>
#include <fstream>
#include <vector>

// extern int score;

std::pair<std::map<std::string, std::string>, std::vector<int> > readConfig(const std::string& filename);
extern "C" void read_line(char*);
extern "C" void slow_put(const char*);
extern "C" void slow_slow_put(const char*);
extern "C" void read_six_numbers(char *, int *);
extern "C" void explode_bomb();
extern "C" void true_ending();
void print_score();

#endif // UTILS_H