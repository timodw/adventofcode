#include <iostream>

#define GEN_A 591
#define GEN_A_FACTOR 16807
#define GEN_B 393
#define GEN_B_FACTOR 48271
#define DIVISOR 2147483647
#define ITERATIONS 40000000

int main() {
    uint64_t sum = 0;
    uint64_t gen_a_val = GEN_A;
    uint64_t gen_b_val = GEN_B;
    for (size_t i = 0; i < ITERATIONS; i++) {
        gen_a_val = (gen_a_val * GEN_A_FACTOR) % DIVISOR;
        gen_b_val = (gen_b_val * GEN_B_FACTOR) % DIVISOR;
        if (((gen_a_val ^ gen_b_val) & 0xFFFF) == 0) sum++;
    }
    std::cout << "SOLUTION: " << sum;
    return 0;
}
