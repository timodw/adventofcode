#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        getline(file, line);
        int start = 0;
        int end = line.find(",");
        int x = 0;
        int y = 0;
        int z = 0;
        int max_distance = 0;
        bool done = false;
        while (!done) {
            std::string mov;
            if (end != std::string::npos) {
                mov = line.substr(start, end - start);
            } else {
                done = true;
                mov = line.substr(start);
            }
            if (mov == "n") {
                y++;
                z--;
            } else if (mov == "s") {
                y--;
                z++;
            } else if (mov == "ne") {
                x++;
                z--;
            } else if (mov == "se") {
                x++;
                y--;
            } else if (mov == "sw") {
                x--;
                z++;
            } else if (mov == "nw") {
                x--;
                y++;
            }
            start = end + 1;
            end = line.find(",", start);
            if ((abs(x) + abs(y) + abs(z))/2 > max_distance) {
                max_distance = (abs(x) + abs(y) + abs(z))/2;
            }
        }
        std::cout << "SOLUTION: " <<  max_distance;
    }
    return 0;
}
