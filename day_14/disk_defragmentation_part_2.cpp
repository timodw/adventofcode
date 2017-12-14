#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#define SIZE 128

std::string input_str("ugkiagan");
std::vector<unsigned char> suffix = {17,31,73,47,23};
std::vector< std::vector<unsigned char> > grid;
int grid_arr[SIZE*SIZE] = {};

std::vector<unsigned char> knot_hash(std::string);
void floodfill(int id, int x, int y);

int main() {
    for (size_t i = 0; i < SIZE; i++) {
        grid.push_back(knot_hash(input_str + "-" + std::to_string(i)));
    }
    int id = 1;
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            unsigned char byte = grid[i][j / 8];
            unsigned char current_bit = byte & 1 << (7 - (j % 8)); 
            if (current_bit != 0 && grid_arr[i * SIZE + j] == 0) {
                floodfill(id++, i, j);
            }
        }
    }
    std::cout << "SOLUTION: " << id - 1;
    return 0;
}

std::vector<unsigned char> knot_hash(std::string orig) {
    int start = 0;
    int skip_size = 0;
    std::vector<unsigned char> input(orig.begin(), orig.end());
    input.insert(input.end(), suffix.begin(), suffix.end());
    std::vector<int> vec(256);
    for (size_t i = 0; i < 256; i++) vec[i] = i;
    for (size_t rounds = 0; rounds < 64; rounds++) {
        for (size_t i = 0; i < input.size(); i++) {
            int len = input[i];
            for (size_t j = 0; j < len / 2; j++) {
                int tmp = vec[(start + len - j - 1) % vec.size()];
                vec[(start + len - j - 1) % vec.size()] = vec[(start + j) % vec.size()];
                vec[(start + j) % vec.size()] = tmp;
            }
            start = (start + skip_size++ + len) % vec.size();
        }
    }

    std::vector<unsigned char> output;
    for (size_t i = 0; i < 16; i++) {
        unsigned char xor_ch = vec[i * 16];
        for (size_t j = 1; j < 16; j++) {
            xor_ch ^= vec[i * 16 + j];
        }
        output.push_back(xor_ch);
    }
    return output;
}

void floodfill(int id, int i, int j) {
    if (i >= 0 && j >= 0 && i < SIZE && j < SIZE && grid_arr[i * SIZE + j] == 0) {
        unsigned char byte = grid[i][j / 8];
        unsigned char current_bit = byte & 1 << (7 - (j % 8)); 
        if (current_bit != 0) {
            grid_arr[i * SIZE + j] = id;
            floodfill(id, i, j + 1);
            floodfill(id, i + 1, j);
            floodfill(id, i, j - 1);
            floodfill(id, i - 1, j);
        }
    }
}
