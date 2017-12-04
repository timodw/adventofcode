#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

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
    std::vector< std::unordered_set<char> > word_letters;
    int start = 0;
    int end = password.find(" ");
    while (end != std::string::npos) {
        std::string word = password.substr(start, end - start);
        std::unordered_set<char> letters;
        for (int i = 0; i < word.size(); i++) {
            letters.insert(word[i]);
        }
        word_letters.push_back(letters);
        start = end + 1;
        end = password.find(" ", start);
    }
    std::string word = password.substr(start, end - start);
    std::unordered_set<char> letters;
    for (int i = 0; i < word.size(); i++) {
        letters.insert(word[i]);
    }
    word_letters.push_back(letters);
    for (int i = 0; i < word_letters.size() - 1; i++) {
        for (int j = i + 1; j < word_letters.size(); j++) {
            if (word_letters[i] == word_letters[j]) return false;
        }
    }
    return true;
}
