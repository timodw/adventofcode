#include <iostream>
#include <vector>
#include <string>
#include <bitset>

std::string input_str("ugkiagan");
std::vector<unsigned char> suffix = {17,31,73,47,23};

std::vector<unsigned char> knot_hash(std::string);

int main() {
    int sum = 0;
    for (size_t i = 0; i < 128; i++) {
        std::vector<unsigned char> knot = knot_hash(input_str + "-" + std::to_string(i));
        for (unsigned char ch: knot) {
            std::bitset<8> byte(ch);
            sum += byte.count();
        }
    }
    std::cout << "SOLUTION: " << sum;
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
