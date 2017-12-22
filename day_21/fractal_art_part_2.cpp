#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

#define ITERATIONS 18

std::unordered_map<std::string, std::string> rules;
std::string grid = ".#...####";

std::string flip(std::string);
std::string rotate(std::string);
void insert_rule(std::string, std::string);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) {
        int64_t start = 0;
        int64_t end = line.find(" ");
        std::string left_side = line.substr(start, end);
        left_side.erase(std::remove(left_side.begin(), left_side.end(), '/'), left_side.end());
        start = end + 4;
        std::string right_side = line.substr(start);
        right_side.erase(std::remove(right_side.begin(), right_side.end(), '/'), right_side.end());
        insert_rule(left_side, right_side);
    }

    for (size_t i = 0; i < ITERATIONS; i++) {
        std::cout << "ITERATION: " << i << std::endl;
        int64_t step_size;
        int64_t size = (int64_t) sqrt((double) grid.size());
        if (size % 2 == 0) {
            step_size = 2;
        } else {
            step_size = 3;
        }
        std::string tmp = "";
        for (size_t x = 0; x < size; x += step_size) {
            for (size_t y = 0; y < size; y += step_size) {
                std::string block = "";
                for (size_t block_row = x; block_row < x + step_size; block_row++) {
                    for (size_t block_col = y; block_col < y + step_size; block_col++) {
                        block = block + grid[block_row * size + block_col];
                    }
                }
                tmp = tmp + rules[block];
            }
        }
        grid = "";
        size = (int64_t) sqrt((double) tmp.size());
        step_size++;
        for (size_t x = 0; x < size; x++) {
            for (size_t y = 0; y < size; y++) {
                int64_t block_row = x / step_size;
                int64_t block_col = y / step_size;
                int64_t block_index = block_row * (size / step_size) + block_col;
                int64_t block_row_index = x % step_size;
                int64_t block_col_index = y % step_size;
                grid = grid + tmp[step_size * step_size * block_index + (block_row_index * step_size + block_col_index)];
            }
        }
    }

    int64_t sum = 0;
    for (char ch: grid) {
        if (ch == '#') sum++;
    }
    std::cout << sum;
    return 0;
}

void insert_rule(std::string lhs, std::string rhs) {
    rules[lhs] = rhs;
    lhs = rotate(lhs); //90 degrees right
    rules[lhs] = rhs;
    lhs = rotate(lhs); //180 degrees right
    rules[lhs] = rhs;
    lhs = rotate(lhs); //270 degrees right
    rules[lhs] = rhs;
    lhs = rotate(lhs); //back to normal

    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = flip(lhs);
    lhs = rotate(lhs); //90 degrees right
    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = rotate(lhs); //180 degrees right
    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = rotate(lhs); //270 degrees right
    lhs = flip(lhs);
    rules[lhs] = rhs;
    lhs = flip(lhs);
    rules[lhs] = rhs;
}

std::string flip(std::string s) {
    int64_t size = s.size() == 4 ? 2: 3;
    std::string out = "";
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            out = out + s[size * i + (size - j - 1)];
        }
    }
    return out;
}

std::string rotate(std::string s) {
    int64_t size = s.size() == 4 ? 2: 3;
    std::string transpose = "";
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            transpose = transpose + s[size * j + i];
        }
    }
    return flip(transpose);
}
