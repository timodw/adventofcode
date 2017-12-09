#include <fstream>
#include <iostream>


int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        char ch;
        bool is_garbage = false;
        int nr_of_left_braces = 0;
        int nr_of_groups = 0;
        while (file.get(ch)) {
            if (!is_garbage) {
                if (ch == '{') {
                    nr_of_left_braces++;
                } else if (ch == '}') {
                    nr_of_groups += nr_of_left_braces;
                    nr_of_left_braces--;
                } else if (ch == '<') {
                    is_garbage = true;
                }
            } else {
                if (ch == '>') {
                    is_garbage = false;
                } else if (ch == '!') {
                    file.get(ch);
                }
            }
        }
        std::cout << "SOLUTION: " << nr_of_groups;
    }
    return 0;
}
