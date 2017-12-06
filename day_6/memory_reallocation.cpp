#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct VectorHash {
    size_t operator() (const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

int main() {
    std::vector<int> input = {4 ,10 ,4 ,1 ,8 ,4 ,9 ,14 ,5 ,1 ,14 ,15 ,0 ,15 ,3 , 5};
    std::unordered_map< std::vector<int>, int, VectorHash > configs;
    int count = 0;
    configs.insert({input, count});
    std::vector<int> banks = std::vector<int>(input);
    for (;;) {
        int index = std::max_element(banks.begin(), banks.end()) - banks.begin();
        int blocks = banks[index];
        banks[index] = 0;
        while (blocks > 0) {
            index = ++index % banks.size();
            banks[index]++;
            blocks--;
        }
        count++;
        if (configs.find(banks) == configs.end()) {
            configs.insert({banks, count});
        } else {
            break;
        }
        banks = std::vector<int>(banks);
    }
    std::cout << "SOLUTION: " << count - configs.find(banks)->second;
    return 0;
}
