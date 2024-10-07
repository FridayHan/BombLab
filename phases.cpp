#include <stdio.h>
#include <string.h>
#include <openssl/evp.h> 
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include "utils.h"
#include "phases.h"

using namespace std;

// ----------------- phase 0 -----------------
int ID_hash = 0;

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

    // printf("Hash as integer:%d\n", ID_hash);
}

// ----------------- phase 1 -----------------

char phase_1_str[] = "In 2024, the rapid advancement of AI continues to reshape society, but it also raises growing concerns. AI systems are becoming increasingly autonomous, often outpacing regulatory frameworks and ethical guidelines. AI's unchecked growth risks losing human control\0, potentially leading to unintended consequences. There is also concern about the concentration of power in a few AI-driven entities, which could manipulate data and outcomes. Now, more than ever, we must balance AI innovation with caution to ensure it benefits humanity rather than threatens it. We must take action to \033[31mcontain AI\033[0m.";
int phase_1_offset;

extern "C" bool string_not_equal(char* src, char* dest) {
    for(int i = 0; dest[i]; i++) {
        if(src[i] != dest[i]) {
            return false;
        }
    }
    return true;
}

void phase_1(char *input) { // ans: AI's unchecked growth risks losing human control
    phase_1_offset = 215 - abs(ID_hash % 10);
    // printf("%d\n", ID_hash % 10);
    // printf("%d\n", phase_1_offset);
    char* answer = phase_1_str + phase_1_offset; 
    if (!string_not_equal(input, answer)) {
        explode_bomb();
    }
}

// ----------------- phase 2 -----------------

#define BASE_IN_2 -10
#define BASE_ADD_2 (ID_hash % 4 + 1)

struct {
    int nums[6] = {2, 4, 8, 16, 32, 64};
    int base = BASE_IN_2;
    int add_num = BASE_ADD_2;
} phase_2_nums;

void phase_2(char *input) { // ans: 1 -6 64 -636 6364 -63636
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

void phase_3(char *input) { // ans: 0 v e r f 1 0 w
    int x, y, z, stage = 0;
    char a, b, c, d, e;
    
    int retval = sscanf(input, "%d %c %c %c %c %d %d %c", &x, &a, &b, &c, &d, &y, &z, &e);

    if (retval != 8) {
        explode_bomb();
    }

    while(stage != 3)
    {
        switch (stage)
        {
            case 7:
                if (d != 'f')
                    explode_bomb();
                stage = 2;
                break;
            
            case 1:
                if (z != 0)
                    explode_bomb();
                stage = 5;
                break;

            case 0:
                if (x != 0)
                    explode_bomb();
                stage = 9;
                break;

            case 8:
                if (b != 'e')
                    explode_bomb();
                stage = 6;
                break;

            case 9:
                if (a != 'v')
                    explode_bomb();
                stage = 8;
                break;
    
            case 5:
                if (e != 'w')
                    explode_bomb();
                stage = 3;
                break;
            
            case 6:
                if (c != 'r')
                    explode_bomb();
                stage = 7;
                break;

            case 2:
                if (y != 1)
                    explode_bomb();
                stage = 1;
                break;
            
            case 53535:
                if (y != 3)
                    explode_bomb();
                stage = 32222;

            default:
                explode_bomb();
        }
    }
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

    int is_phase5_passable(int id_hashed) { return restrictionWeight >= 75 && id_hashed == ID_hash % 0x1000; }
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

void phase_5(char* input) { // ans: growth 2034 (<ID_hash> % 1000)
    AIRegulator *regulator = nullptr;

    char regulation[15];
    int year;
    int id_hashed;

    if (sscanf(input, "%s %d %x", regulation, &year, &id_hashed) != 3)
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
        {2, &stackBottom, &initialNodes[1]},        // 0
        {4, &initialNodes[1], &initialNodes[3]},    // 1
        {8, &initialNodes[2], &initialNodes[4]},    // 2
        {16, &initialNodes[3], &initialNodes[5]},    // 3
        {32, &initialNodes[4], &initialNodes[6]},    // 4
        {64, &initialNodes[5], &stackTop}            // 5
};

extern "C" int get_stack_top(node*& ptr) {
    int val = ptr->val;
    return val;
}

extern "C" void stack_push(node*& ptr, int val) {
    ptr->val = val;
    ptr = ptr->next;
}

extern "C" void stack_pop(node*& ptr) {
    ptr = ptr->prev;
}

extern "C" node* build_stack() {
    stackBottom.next = &initialNodes[0];
    stackTop.prev = &initialNodes[5];
    return stackBottom.next;
}

extern "C" bool check_answer() {
    node* curr = stackBottom.next;
    for (; curr != stackTop.prev; curr = curr->next) { // the first 5 nodes
        if (curr->val < curr->prev->val) { // prev > curr, BOOM; need: prev <= curr
            return 0;
        }
    }
    return 1;
}

extern "C" bool maintain_monotonic_sequence(node* ptr, int val) {
    if (stackBottom.val > val) { // val needs to be larger than stackBottom.val(3)
        return false;
    }
    while (ptr != &stackBottom || ptr->val > val) {
        stack_pop(ptr); // pop until ptr == stackBottom or ptr->val <= val
    }
    stack_push(ptr, val);
    return true;
}

void phase_6(char* input) { // ans: 4 4 4 4 4 4 (or any increasing sequence with the first element >= 4)
    read_six_numbers(input, phase_6_nums.nums);
    printf("Valid Input\n");
    int* nums = phase_6_nums.nums;
    for (int i = 0; i < PHASE6_INPUT_LEN; ++i) {
        if (nums[i] > 6 || nums[i] < 0) { // check: 0 <= nums[h] <= 6
            explode_bomb();
        }
    }

    bool valid = true;
    node* stackPtr = build_stack();
    for (int i = 0; i < PHASE6_INPUT_LEN; ++i) {
        valid &= maintain_monotonic_sequence(stackPtr, nums[i]);
    }
    if (!valid) {
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
