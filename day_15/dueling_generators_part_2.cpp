#include <iostream>

#define GEN_A 591
#define GEN_A_FACTOR 16807
#define GEN_B 393
#define GEN_B_FACTOR 48271
#define DIVISOR 2147483647
#define ITERATIONS 5000000

bool judge(uint64_t, uint64_t);
uint64_t get_next_val(bool);

uint64_t gen_a_val = GEN_A;
uint64_t gen_b_val = GEN_B;

int main() {
    uint64_t sum = 0;
    for (size_t i = 0; i < ITERATIONS; i++) {
        if (judge(get_next_val(true), get_next_val(false))) sum++;
    }
    std::cout << "SOLUTION: " << sum;
    return 0;
}

bool judge(uint64_t gen_a, uint64_t gen_b) {
    return ((gen_a ^ gen_b) & 0xFFFF) == 0;
}

uint64_t get_next_val(bool is_gen_a) {
    if (is_gen_a) {
        gen_a_val = (gen_a_val * GEN_A_FACTOR) % DIVISOR;
        while (gen_a_val % 4 != 0) {
            gen_a_val = (gen_a_val * GEN_A_FACTOR) % DIVISOR;
        }
        return gen_a_val;
    } else {
        gen_b_val = (gen_b_val * GEN_B_FACTOR) % DIVISOR;
        while (gen_b_val % 8 != 0) {
            gen_b_val = (gen_b_val * GEN_B_FACTOR) % DIVISOR;
        }
        return gen_b_val;
    }
}
