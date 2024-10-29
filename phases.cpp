#include <stdio.h>
#include <string.h>
#include <openssl/evp.h> 
#include <cstdlib>
#include "utils.h"
#include "phases.h"
#include "colors.h"

using namespace std;

// ----------------- phase 0 -----------------
unsigned int ID_hash = 0;

void phase_0(std::string input) {
    const string student_id = (string)input;
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    EVP_DigestInit_ex(context, md, nullptr);
    EVP_DigestUpdate(context, student_id.c_str(), student_id.size());
    EVP_DigestFinal_ex(context, hash, &lengthOfHash);
    EVP_MD_CTX_free(context);

    for (size_t i = 0; i < sizeof(int); ++i) {
        ID_hash = (ID_hash << 8) | hash[i];
    }
}

// ----------------- phase 1 -----------------

char phase_1_str[] = "In 2024, the rapid advancement of AI continues to reshape society, but it also raises growing concerns. AI systems are becoming increasingly autonomous, often outpacing regulatory frameworks and ethical guidelines. AI's unchecked growth risks losing human control\0, potentially leading to unintended consequences. There is also concern about the concentration of power in a few AI-driven entities, which could manipulate data and outcomes. Now, more than ever, we must balance AI innovation with caution to ensure it benefits humanity rather than threatens it. We must take action to " RED "contain AI" RESET ".";
int phase_1_offset;

extern "C" bool string_not_equal(char* src, char* dest) {
    for(int i = 0; dest[i]; i++) {
        if(src[i] != dest[i]) {
            return false;
        }
    }
    return true;
}

void phase_1(char *input) { // ans: <ID_hash%10 of more char>AI's unchecked growth risks losing human control
    phase_1_offset = 215 - ID_hash % 10;
    char* answer = phase_1_str + phase_1_offset; 
    if (!string_not_equal(input, answer)) {
        explode_bomb();
    }
}

// ----------------- phase 2 -----------------

void phase_2(char *input) {
    // ans(0): 1 -9 91 -909 9091 -90909
    // ans(1): 1 -8 82 -818 8182 -81818
    // ans(2): 1 -7 73 -727 7273 -72727 
    // ans(3): 1 -6 64 -636 6364 -63636
    struct {
        int nums[6] = {2, 4, 8, 16, 32, 64};
        int base = -10;
        int add_num = ((ID_hash % 4) + 1);
    } phase_2_nums;
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

void phase_3(char *input) { // ans: 1 1 o / 2 3 v / 5 8 e / 13 21 r / 34 55 f / 89 144 l / 233 377 o / 610 987 w
    int x, y;
    char c, c_chk;
    
    int check = ID_hash % 8;
    
    int retval = sscanf(input, "%d %d %c", &x, &y, &c);

    if (retval != 3) {
        explode_bomb();
    }

    switch (x)
    {
        case 1:
            c_chk = 'o';
            if (y != 1 || check != 0) 
                explode_bomb();
            break;

        case 2:
            c_chk = 'v';
            if (y != 3 || check != 1)
                explode_bomb();
            break;

        case 5:
            c_chk = 'e';
            if (y != 8 || check != 2)
                explode_bomb();
            break;

        case 13:
            c_chk = 'r';
            if (y != 21 || check != 3)
                explode_bomb();
            break;

        case 34:
            c_chk = 'f';
            if (y != 55 || check != 4)
                explode_bomb();
            break;

        case 89:
            c_chk = 'l';
            if (y != 144 || check != 5)
                explode_bomb();
            break;

        case 233:
            c_chk = 'o';
            if (y != 377 || check != 6)
                explode_bomb();
            break;
        
        case 610:
            c_chk = 'w';
            if (y != 987 || check != 7)
                explode_bomb();
            break;

        default:
            explode_bomb();
    }

    if (c != c_chk)
        explode_bomb();
}

// ----------------- phase 4 -----------------

#define POW_BASE 8

static int CIE(int n) {
    if(!n) return 1;
    int half = CIE(n >> 1);
    if (n & 1) return half * half * POW_BASE;
    else return half * half;
}

void phase_4(char* input) { // ans 42949672961 ~ 42949672970
    long long num;
    int n, m;
    
    if (sscanf(input, "%lld", &num) != 1)
        explode_bomb();

    n = (int)(num >> 32);           // n stands for the high 32 bits
    m = (int)(num & 0xffffffff);    // m stands for the low 32 bits

    if ((n <= 0) | (n >= 0xb) | (m <= 0) | (m >= 0xb)) // need: 1 <= n, m <= 10
        explode_bomb();
    
    if (CIE(n) != 1073741824) // n != 10 (10 << 32 = 42949672960)
        explode_bomb();
}

// ----------------- phase 5 -----------------

class AIRegulator {
protected:
    int restrictionWeight = 0;
public:
    AIRegulator() {}
    ~AIRegulator() {}

    virtual int imposeLimit() = 0;
    virtual int enforcePenalty() = 0;
    virtual int triggerIntervention(int year) = 0;

    int is_phase5_passable(unsigned int id_hashed) { return restrictionWeight >= 75 && id_hashed == ID_hash % 0x1000; }
};

class AIBehaviorRegulator : public AIRegulator {
public:
    AIBehaviorRegulator() { restrictionWeight = 50; }
    ~AIBehaviorRegulator() {}

    int imposeLimit() { return 0x10; }
    int enforcePenalty() { return 0x10; }

    int triggerIntervention(int year) {
        return year == 2027;
    }
};

class AIEthicsRegulator : public AIRegulator {
public:
    AIEthicsRegulator() { restrictionWeight = 70; }
    ~AIEthicsRegulator() {}

    int imposeLimit() { return 0x1; }
    int enforcePenalty() { return 0x1000; }

    int triggerIntervention(int year) {
        return year == 2030;
    }
};

class AIGrowthRegulator : public AIRegulator {
public:
    AIGrowthRegulator() { restrictionWeight = 90; }
    ~AIGrowthRegulator() {}

    int imposeLimit() { return 0x100; }
    int enforcePenalty() { return 0x100; }

    int triggerIntervention(int year) {
        return year == 2034;
    }
};

void phase_5(char* input) { // ans: growth 2034 <ID_hash%0x1000>
    AIRegulator *regulator = nullptr;

    char regulation[15];
    int year;
    unsigned int id_hashed;

    if (sscanf(input, "%s %d %u", regulation, &year, &id_hashed) != 3)
        explode_bomb();

    if (strcmp(regulation, "behavior") == 0) {
        regulator = new AIBehaviorRegulator();
    } else if (strcmp(regulation, "ethics") == 0) {
        regulator = new AIEthicsRegulator();
    } else if (strcmp(regulation, "growth") == 0) {
        regulator = new AIGrowthRegulator();
    } else {
        explode_bomb();
    }

    if (!regulator->triggerIntervention(year) || !regulator->is_phase5_passable(id_hashed))
        explode_bomb();
}

// ----------------- phase 6 -----------------

#define STACK_SIZE 6
#define PHASE6_INPUT_LEN 6

struct {
    int nums[6] = {2, 4, 8, 16, 32, 64};
} phase_6_nums;

struct node {
    int val;
    struct node *prev;
    struct node *next;
};

node stackBottom = {4, nullptr, nullptr};
node stackTop = {0, nullptr, nullptr};

node initialNodes[STACK_SIZE] = {
        {0x10, &stackBottom, &initialNodes[1]},         // 0
        {0x20, &initialNodes[0], &initialNodes[2]},     // 1
        {0x40, &initialNodes[1], &initialNodes[3]},     // 2
        {0x80, &initialNodes[2], &initialNodes[4]},     // 3
        {0x100, &initialNodes[3], &initialNodes[5]},    // 4
        {0x200, &initialNodes[4], &stackTop}            // 5
};

extern "C" int get_stack_top(node*& ptr) {
    int val = ptr->val;
    return val;
}

extern "C" void stack_push(node*& ptr, int val) { // ptr points to the top of the stack
    ptr = ptr->next; // the next node is the new top
    ptr->val = val;
}

extern "C" void stack_pop(node*& ptr) {
    ptr->val = 0;
    ptr = ptr->prev;
}

extern "C" node* build_stack() {
    stackBottom.next = &initialNodes[0];
    stackTop.prev = &initialNodes[5];
    return stackTop.prev; // the real top of the stack
}

extern "C" bool check_answer() {
    node* curr = stackBottom.next;
    for (; curr != &stackTop; curr = curr->next) {
        if (curr->val < curr->prev->val) { // prev > curr, BOOM; need: prev <= curr
            return false;
        }
    }
    return true;
}

extern "C" void maintain_monotonic_sequence(node*& ptr, int val) {
    while (ptr != &stackBottom && ptr->val > val) {
        stack_pop(ptr); // pop until ptr == stackBottom or ptr->val <= val
    }
    stack_push(ptr, val);
}

void phase_6(char* input) { // ans: 4 4 4 4 4 4 (or any increasing sequence with the first element >= 4)
    read_six_numbers(input, phase_6_nums.nums);

    int* nums = phase_6_nums.nums;
    for (int i = 0; i < PHASE6_INPUT_LEN; ++i) {
        if (nums[i] > 6 || nums[i] < 0) { // check: 0 <= nums[h] <= 6
            explode_bomb();
        }
    }

    node* stackPtr = build_stack();
    for (int i = 0; i < PHASE6_INPUT_LEN; ++i) {
        maintain_monotonic_sequence(stackPtr, nums[i]);
    }
    if (!check_answer()) {
        explode_bomb();
    }
}

// ----------------- secret phase -----------------

// Entrance:
// In any phase, add lots of characters after the correct password to overflow into the `secret_key`

typedef enum {
    S0, // initial state
    S1, // state 1
    S2, // state 2
    S3, // state 3
    R   // reject state (explode in the next iteration)
} State;

void secret_phase(char* input) { // ans: CIE
    State state = S0;
    for (int i = 0; i < 3; ++i) {
    // for (int i = 0; input[i] != '\0'; ++i) {
        if (((input[i] - 'A') & 1) || (input[i] > 'J')) { // only accept 'A', 'C', 'E', 'G', 'I'
            explode_bomb();
        }
        switch (state) {
            case S0:
                if (input[i] == 'C') {
                    state = S1;
                } else if (input[i] == 'A' || input[i] == 'G') {
                    state = R;
                } else { // I, E
                    explode_bomb();
                }
                break;
            case S1:
                if (input[i] == 'I') {
                    state = S2;
                } else if (input[i] == 'C' || input[i] == 'E') {
                    state = R;
                } else { // A, G
                    explode_bomb();
                }
                break;
            case S2:
                if (input[i] == 'E') {
                    state = S3;
                } else if (input[i] == 'I') {
                    state = S2;
                } else { // C, A, G
                    explode_bomb();
                }
                break;
            case R:
                explode_bomb();
                break;
            default:
                explode_bomb();
                break;
        }
    }
    if (state != S3) { // final check
        explode_bomb();
    }
}
