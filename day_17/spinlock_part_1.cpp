#include <iostream>
#include <vector>

#define INPUT 371
#define ITERATIONS 2017

int main() {
    std::vector<int> buffer;
    buffer.push_back(0);
    size_t position = 0;
    for (size_t i = 0; i < ITERATIONS; i++) {
        position = (position + INPUT) % buffer.size();
        buffer.insert(buffer.begin() + position++, i + 1);
    }
    std::cout << "SOLUTION: " << buffer[position % buffer.size()];
    return 0;
}


