#include <iostream>
#include <vector>

#define INPUT 371
#define ITERATIONS 50000000

int main() {
    std::vector<int> buffer;
    uint32_t size = 1;
    uint32_t answer = 0;
    size_t position = 0;
    for (size_t i = 0; i < ITERATIONS; i++) {
        position = (position + INPUT) % size++;
        if (position++ == 0) answer = i + 1;
    }
    std::cout << "SOLUTION: " << answer;
    return 0;
}


