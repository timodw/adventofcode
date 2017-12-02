#include <iostream>
#include <fstream>
#include <vector>

int calculate(std::vector<char>&);

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        char number; 
        std::vector<char> numbers;
        while (file.get(number)) {
            numbers.push_back(number - 48);
        }
        int sol = calculate(numbers);
        std::cout << "SOLUTION: " << sol << std::endl;
    }
    return 0;
}

int calculate(std::vector<char>& numbers) {
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[(i + 1) % numbers.size()] == numbers[i]) {
            sum += numbers[i];
        }
    }
    return sum;
}
