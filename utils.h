#ifndef UTILS_H
#define UTILS_H
#include <map>
#include <string>
#include <fstream>

std::map<std::string, std::string> readConfig(const std::string&);
extern "C" void read_line(char*);
extern "C" void slow_put(const char*);
extern "C" void slow_slow_put(const char*);
extern "C" void read_six_numbers(char *, int *);
extern "C" void explode_bomb();
extern "C" void true_ending();

#endif // UTILS_H