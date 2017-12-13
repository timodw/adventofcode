#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::unordered_map<int, int> wall;
    while (getline(file, line)) {
        int end = line.find(":");
        int layer = std::stoi(line.substr(0, end));
        int depth = std::stoi(line.substr(end + 2));
        wall[layer] = depth;
    }
    int delay = 0;
    bool caught = true;
    while (caught) {
        caught = false;
        for (auto it: wall) {
            if ((it.first + delay) % ((it.second - 1) * 2) == 0) { 
                caught = true;
                delay++;
                break;
            }
        }
    }

    std::cout << "SOLUTION: " << delay;
    return 0;
}
