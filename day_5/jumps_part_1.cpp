#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<int> jumps;
        while (getline(file, line)) {
            jumps.push_back(atoi(line.c_str()));
        }
        int64_t pc = 0;
        uint64_t nr_of_steps = 0;
        while (pc >= 0 && pc < jumps.size()) {
            pc += jumps[pc]++;
            nr_of_steps++;
        }
        std::cout << "SOLUTION: " << nr_of_steps;
    }
    return 0;
}
