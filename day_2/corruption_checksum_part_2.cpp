#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> split_string(std::string, std::string); 
int calculate(const std::vector<int>&);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int total_sum = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            total_sum += calculate(split_string("\t", line));
        }
    }
    std::cout << "SOLUTION: " << total_sum << std::endl;
}

std::vector<int> split_string(std::string delimiter, std::string line) {
    std::vector<int> values;
    int start = 0;
    int end = line.find(delimiter);
    while (end != std::string::npos) {
        values.push_back(atoi(line.substr(start, end - start).c_str()));
        start = end + delimiter.length();
        end = line.find(delimiter, start);
    }
    values.push_back(atoi(line.substr(start, end - start).c_str()));
    return values;
}

int calculate(const std::vector<int>& values) {
    for (int i = 0; i < values.size() - 1; i++) {
        for (int j = i + 1; j < values.size(); j++) {
            if (values[i] < values[j]) {
                if (values[j] % values[i] == 0) {
                    return values[j] / values[i];
                }
            } else {
                if (values[i] % values[j] == 0) {
                    return values[i] / values[j];
                }
            }
        }
    }

    return 0;
}
