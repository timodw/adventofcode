#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int total_sum = 0;
    while (getline(file, line)) {
        int end = line.find(":");
        int layer = std::stoi(line.substr(0, end));
        int depth = std::stoi(line.substr(end + 2));
        if (layer % ((depth - 1)  * 2) == 0) total_sum += layer*depth;
    }
    std::cout << "SOLUTION: " << total_sum;
    return 0;
}
