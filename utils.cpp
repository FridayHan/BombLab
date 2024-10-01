#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void explode_bomb() {
    printf("BOOM!!!\n");

    // try open fail.txt
    FILE* fp;
    if ((fp = fopen("fail.txt", "r")) == NULL)
        exit(1);

    while (!feof(fp))
    {
        char ch = fgetc(fp);
        if (ch != EOF)
            putchar(ch);
    }

    fclose(fp);

    exit(1);
}

// put a string to stdout, one character at a time, interval 0.1s
void slow_put(const char* str)
{
    while (*str != '\0')
    {
        putchar(*str);
        str++;

        struct timespec ts;
        ts.tv_sec = 0;
        // ts.tv_nsec = 15000000;
        ts.tv_nsec = 50000000;
        nanosleep(&ts, NULL);

        fflush(stdout);
    }
}

void slow_slow_put(const char* str)
{
    while (*str != '\0')
    {
        putchar(*str);
        str++;

        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 300000000;
        nanosleep(&ts, NULL);

        fflush(stdout);
    }
}

void read_six_numbers(char *buf, int *nums)
{
    int nums_read = sscanf(buf, "%d %d %d %d %d %d", &nums[0], &nums[1],
            &nums[2], &nums[3], &nums[4], &nums[5]);
    if (nums_read != 6 || !nums[0])
        explode_bomb();
}

void true_ending()
{
    puts("You have successfully defused the bomb!");
}