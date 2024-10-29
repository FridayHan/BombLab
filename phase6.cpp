/*
 * 这是下发的版本，实际上写的错的离谱。。
 * phase.cpp 里的 phase_6 改成理想中的样子了，去参考那个吧。。
 * 在此忏悔。
 * 
 * 细数罪行：
 * 1. initialNodes 初始化错了，而且不应该设小的初始值，会影响栈的 pop
 * 2. 栈顶指针不该指向顶之上（空元素），应该指向有内容的那个栈顶（对于 stack_push 操作）
 * 3. maintain_monotonic_sequence 的参数应该是引用，否则不会改外面那个指针
 * 4. maintain_monotonic_sequence 中的 while 条件更是错的离谱。不该是 ||，应该是 &&
 * 5. 实际上 maintain_monotonic_sequence 的 while 改对后，也不需要再和那个虚假栈底比大小了
 * 6. check_answer 没用上，不过里面的 for 也是错的（还好没用上），应该是 != stackTop，到栈顶为止，比较六个元素（因为有 stackBottom 垫着，不会超出去）
 * （可能还有别的，数不动了。原本我还一直以为没问题的，直到有人来详细问这题在干什么。。。）
 * 
 * 对这题竟然最后效果和想象中一样深感震惊。
 * （实际：只看 stackBottom 和 initialNodes[0]，而 initialNodes[0] 是 2，要求输入的不小于 4，所以一定会遇到一个 pop 操作
 *  也就是说给出去的题目实际上在反复覆写 stackBottom，然后要求每次输入的数比 stackBottom 大，所以最后确实还是一个非减数列。。。）
 * 
 * 唉太废物了。TA 失格。
 */

#include "utils.h"

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
    if (stackBottom.val > val) { // val needs to be larger than stackBottom.val(4)
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
    // printf("Valid Input\n");
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
