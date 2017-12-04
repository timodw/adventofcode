#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool check_password(std::string);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int count = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (check_password(line)) count++;
        }
    }
    std::cout << "SOLUTION: " << count;
    return 0;
}

bool check_password(std::string password) {
    std::vector<std::string> words;
    int start = 0;
    int end = password.find(" ");
    while (end != std::string::npos) {
        words.push_back(password.substr(start, end - start));
        start = end + 1;
        end = password.find(" ", start);
    }
    words.push_back(password.substr(start, end - start)); 
    std::sort(words.begin(), words.end());
    for (int i = 0; i < words.size() - 1; i++) {
        if (words[i] == words[i + 1]) return false;
    }
    return true;
}
