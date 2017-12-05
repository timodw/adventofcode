#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<int64_t> jumps;
        while (getline(file, line)) {
            jumps.push_back(atoi(line.c_str()));
        }
        uint64_t pc = 0;
        uint64_t nr_of_steps = 0;
        while (pc < jumps.size()) {
            int64_t offset = jumps[pc];
            uint64_t old_pc = pc;
            pc += offset;
            if (offset < 3) {
                offset++;
            } else {
                offset--;
            }
            jumps[old_pc] = offset;
            nr_of_steps++;
        }
        std::cout << "SOLUTION: " << nr_of_steps;
    }
    return 0;
}
