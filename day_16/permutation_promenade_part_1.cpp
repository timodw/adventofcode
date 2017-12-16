#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

std::string positions = "abcdefghijklmnop";
std::unordered_map<char, int> pos_map = {{'a', 0},
    {'b', 1},
    {'c', 2},
    {'d', 3},
    {'e', 4},
    {'f', 5},
    {'g', 6},
    {'h', 7},
    {'i', 8},
    {'j', 9},
    {'k', 10},
    {'l', 11},
    {'m', 12},
    {'n', 13},
    {'o', 14},
    {'p', 15}}; 

void perform_move(std::string);

int main() {
    std::ifstream file("input.txt");
    std::string input;
    getline(file, input);
    int start = 0;
    int end = input.find(",");
    while (end != std::string::npos) {
        perform_move(input.substr(start, end - start));
        start = end + 1;
        end = input.find(",", start);
    }
    perform_move(input.substr(start));
    std::cout << positions;
    return 0;
}

void perform_move(std::string mov) {
    if (mov[0] == 's') {
        int shift = std::stoi(mov.substr(1));
        std::rotate(positions.begin(), positions.end() - shift, positions.end());
        for (auto& it: pos_map) {
            it.second = (it.second + shift) % pos_map.size();
        }
    } else if (mov[0] == 'x') {
        int slash = mov.find("/");
        int first_index = std::stoi(mov.substr(1, slash - 1));
        int second_index = std::stoi(mov.substr(slash + 1));
        char first_ch = positions[first_index];
        char second_ch = positions[second_index];
        pos_map[first_ch] = second_index;
        pos_map[second_ch] = first_index;
        positions[first_index] = second_ch;
        positions[second_index] = first_ch;
    } else if (mov[0] == 'p') {
        int slash = mov.find("/");
        char first_ch = mov.substr(1, slash - 1)[0];
        char second_ch = mov.substr(slash + 1)[0];
        int first_index = pos_map[first_ch];
        int second_index = pos_map[second_ch];
        pos_map[first_ch] = second_index;
        pos_map[second_ch] = first_index;
        positions[first_index] = second_ch;
        positions[second_index] = first_ch;
    }
}
