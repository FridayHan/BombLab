#include <bits/stdc++.h>
#include "utils.h"
#include "phases.h"

using namespace std;

// ----------------- phase 1 -----------------

char phase_1_str[] = "This text introduced the main ideas in 2023csapp staffms by studying one operating system\0\0\0ics, line by line\0 Some code lines embody the essence of the main ideas\0 (e\0g\0, context switching, user/kernel boundary, locks, etc\0) and 2023ICS Computer science is not a boring subject\0, but a colorful world worth exploring with one's own hands.\0 Our Labs still have many flaws, but we hope that these Labs can be as challenging as games and help everyone truly master the basic skills needed to explore the computer world.\0 If it can stimulate interest in a certain field, it would be really great.\0Wishing all students success in the course!\0yyyyylxxxx\0";
int phase_1_offset = 238;

extern "C" bool string_not_equal(char* src, char* dest) {
    for(int i = 0; dest[i]; i++) {
        if(src[i] != dest[i]) {
            return false;
        }
    }
    return true;
}

void phase_1(char *input) {// ans: Computer science is not a boring subject

    char* answer = phase_1_str + phase_1_offset; 
    if (!string_not_equal(input, answer)) {
        explode_bomb();
    }
}

// ----------------- phase 2 -----------------

#define BASE_IN_2 -4
#define BASE_ADD_2 1

struct {
    int nums[6] = {2, 4, 8, 16, 32, 64};
    char is_pass_six = '\0'; // for secret phase
    int base = BASE_IN_2;
    int add_num = BASE_ADD_2;
} phase_2_nums;

void phase_2(char *input) {//ans: 1 -3 13 -51 205 -819, etc.
    read_six_numbers(input, phase_2_nums.nums); 

    int* nums = phase_2_nums.nums;
    for (auto h = 1; h < 6; h++) {
        int res = phase_2_nums.base * nums[h - 1] + phase_2_nums.add_num;
        if (res != nums[h]) {
            explode_bomb();
        }
    }
}

// ----------------- phase 3 -----------------

void phase_3(char *input) {//ans: 1 1 o
    int x, y;
    char c, c_chk;
    
    int retval = sscanf(input, "%d %d %c", &x, &y, &c);

    if (retval != 3) {
        explode_bomb();
    }

    switch (x)
    {
        case 1:
            c_chk = 'o';
            if (y != 1) 
                explode_bomb();
            break;

        case 2:
            c_chk = 'v';
            if (y != 3)
                explode_bomb();
            break;

        case 5:
            c_chk = 'e';
            if (y != 8)
                explode_bomb();
            break;

        case 13:
            c_chk = 'r';
            if (y != 21)
                explode_bomb();
            break;

        case 34:
            c_chk = 'f';
            if (y != 55)
                explode_bomb();
            break;

        case 89:
            c_chk = 'l';
            if (y != 144)
                explode_bomb();
            break;

        case 233:
            c_chk = 'o';
            if (y != 377)
                explode_bomb();
            break;
        
        case 610:
            c_chk = 'w';
            if (y != 987)
                explode_bomb();
            break;

        default:
            explode_bomb();
    }

    if (c != c_chk)
        explode_bomb();
}

// ----------------- phase 4 -----------------

#define POW_BASE 4

static int hope(int n) {
    if(!n) return 1;
    int half = hope(n >> 1);
    if (n & 1) return half * half * POW_BASE;
    else return half * half;
}

void phase_4(char* input) { // ans 51539607553 ~ 51539607566
    int n, m, num;
    
    if (sscanf(input, "%d", &num) != 1)
        explode_bomb();

    n = (int)(num >> 32);
    m = (int)(num & 0xffffffff);

    if ((n <= 0) | (n >= 0xf) | (m <= 0) | (m >= 0xf)) // consider this the ans is 51539607553
        explode_bomb();
    
    if (hope(n) != 16777216) // n != 12 << 32 which is 51539607552
        explode_bomb();
}

// ----------------- phase 5 -----------------

class worldline
{
protected:
    long divergence;
public:
    worldline() {}
    ~worldline() {}

    virtual int isWorldPeace() = 0;     // only for distraction
    virtual int isEveryoneEqual() = 0;  // only for distraction

    virtual int dmail(int target) = 0;

    int is_phase5_passable() { return divergence >= 1000000; }
};

class worldline1 : public worldline
{
    public:
    worldline1() { divergence = 571024; }
    ~worldline1() {}

    int isWorldPeace() { return 0; }
    int isEveryoneEqual() { return 1; }

    int dmail(int target) {
        return target == 2018;
    }
};

class worldline2 : public worldline
{
    public:
    worldline2() { divergence = 456914; }
    ~worldline2() {}

    int isWorldPeace() { return 1; }
    int isEveryoneEqual() { return 0; }

    int dmail(int target) {
        return target == 2021;
    }
};

class worldline3 : public worldline
{
    public:
    worldline3() { divergence = 1123581;}
    ~worldline3() {}

    int isWorldPeace() { return 1; }
    int isEveryoneEqual() { return 1; }

    int dmail(int target) {
        return target == 2023;
    }
};

void phase_5(char *input) {// ans: 冲冲冲~ 2023
    worldline *tl;

    char dmail[17];
    int target;

    if (sscanf(input, "%s %d", dmail, &target) != 2)
        explode_bomb();

    if (strcmp(dmail, "杀杀杀！") == 0) {
        tl = new worldline1();
    } else if (strcmp(dmail, "退退退。") == 0) {
        tl = new worldline2();
    } else if (strcmp(dmail, "冲冲冲~") == 0) {
        tl = new worldline3();
    } else {
        explode_bomb();
    }

    if (!tl->dmail(target) || !tl->is_phase5_passable())
        explode_bomb();
}

// ----------------- phase 6 -----------------

#define QUEUE_SIZE 6
#define QUEUE_BEGIN 4
#define PHASE6_INPUT_LEN 6

struct{
    int nums[6] = {2 ,4, 8, 16, 32, 64};
} phase_6_nums;

struct node{
    int val;
    struct node *next;
};

node initialNodes[QUEUE_SIZE] = {
        {60, &initialNodes[5]}, //0  
        {10, &initialNodes[3]}, //1  
        {50, &initialNodes[1]}, //2  
        {30, &initialNodes[4]}, //3  
        {20, &initialNodes[0]}, //4    
        {40, &initialNodes[2]}  //5   
};

extern "C" void put_val(node*& rear, int val) {
    rear->val = val;
    rear = rear->next;
}

extern "C" int get_val(node*& front) {
    int val = front->val;
    front = front->next;
    return val;
}

extern "C" node* build_queue() {
    return &initialNodes[QUEUE_BEGIN];
}

extern "C" bool check_answer(int *resultArray){
    int isIncreasing = 1;
    for (int i = 1; i < QUEUE_SIZE; i++) {
        if (resultArray[i] < resultArray[i - 1]) {
            isIncreasing = 0;
            return 0;
        }
    }
    return 1;
}

extern "C" bool build_target(int *nums){
    node* front = nullptr;
    node* rear = nullptr;
    auto queue = build_queue();
    front = queue;
    rear = queue;
    int resultArray[QUEUE_SIZE];

    for (int i = 0; i < PHASE6_INPUT_LEN; i++) {
        int dequeueCount = nums[i];
        int output[dequeueCount];

        for(int j=0;j<dequeueCount;j++){
            output[j]=get_val(front);
        }
        
        resultArray[i]=output[dequeueCount-1];

        for(int j = dequeueCount - 1;j>=0;j--){
            put_val(rear,output[j]);
        }
    }

    // don't forget to free the memory(

    bool res = check_answer(resultArray);
    return res;
}

void phase_6(char* input) { // ans: 5 6 6 4 4 6
    read_six_numbers(input, phase_6_nums.nums); 
    int* nums = phase_6_nums.nums;
    for (auto h = 0; h < PHASE6_INPUT_LEN; h++) {
        if(nums[h] > 6 || nums[h] < 0)
            explode_bomb();
    }

    bool res = build_target(nums);
    if(!res) {
        explode_bomb();
    }
}

// ----------------- secret phase -----------------

// Entrance:
// In any phase, add lots of characters after the correct password to overflow into the `secret_key`

void secret_phase(char *input) {//ans: 1677734099

    /* Junk Instructions
     *  ebff -> jmp -1
     *  ffc0 -> inc eax
     *  ffc8 -> dec eax */
    asm(".byte 0xeb, 0xff, 0xc0, 0xff, 0xc8");
    
    unsigned int num;
    unsigned int key = 0xdeadc0de;

    sscanf(input, "%ud", &num);
    num ^= key;

    if (num != 0xbaadf00d)
        explode_bomb();
}
