#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

std::string input_str = "14,58,0,116,179,16,1,104,2,254,167,86,255,55,122,244";
std::vector<unsigned char> input(input_str.begin(), input_str.end());
std::vector<unsigned char> suffix = {17,31,73,47,23};

std::vector<int> init_list();

int main() {
    int start = 0;
    int skip_size = 0;
    std::vector<int> vec = init_list();
    input.insert(input.end(), suffix.begin(), suffix.end());
    for (int rounds = 0; rounds < 64; rounds++) {
        for (int i = 0; i < input.size(); i++) {
            int len = input[i];
            for (int j = 0; j < len / 2; j++) {
                int tmp = vec[(start + len - j - 1) % vec.size()];
                vec[(start + len - j - 1) % vec.size()] = vec[(start + j) % vec.size()];
                vec[(start + j) % vec.size()] = tmp;
            }
            start = (start + skip_size++ + len) % vec.size();
        }
    }

    std::vector<unsigned char> output;
    for (int i = 0; i < 16; i++) {
        unsigned char xor_ch = vec[i * 16];
        for (int j = 1; j < 16; j++) {
            xor_ch ^= vec[i * 16 + j];
        }
        output.push_back(xor_ch);
    }
    std::cout << "SOLUTION: " ;
    for (unsigned char ch: output) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned int) ch;
    }
    return 0;
}

std::vector<int> init_list() {
    std::vector<int> vec(256);
    for (int i = 0; i < 256; i++) vec[i] = i;
    return vec;
}
