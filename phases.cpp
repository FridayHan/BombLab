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
#define BASE_ADD_2 4

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

    while(stage != 114514)
    {
        switch (stage)
        {
            case 5201314:
                if (d != 'f')
                    explode_bomb();
                stage = 66666;
                break;
            
            case 23333:
                if (z != 0)
                    explode_bomb();
                stage = 785234372;
                break;

            case 0:
                if (x != 0)
                    explode_bomb();
                stage = 3329;
                break;

            case 5770713:
                if (b != 'e')
                    explode_bomb();
                stage = 2330713;
                break;

            case 3329:
                if (a != 'v')
                    explode_bomb();
                stage = 5770713;
                break;
    
            case 785234372:
                if (e != 'w')
                    explode_bomb();
                stage = 114514;
                break;
            
            case 2330713:
                if (c != 'r')
                    explode_bomb();
                stage = 5201314;
                break;

            case 66666:
                if (y != 1)
                    explode_bomb();
                stage = 23333;
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

    int is_phase5_passable(int id_hashed) { return restrictionWeight >= 75 && id_hashed == ID_hash; }
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

void phase_5(char* input) { // ans: growth 2034 <ID_hash>
    AIRegulator *regulator = nullptr;

    char regulation[15];
    int year;
    int id_hashed;

    if (sscanf(input, "%s %d %d", regulation, &year, &id_hashed) != 3)
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
