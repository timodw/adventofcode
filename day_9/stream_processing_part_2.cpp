#include <fstream>
#include <iostream>


int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        char ch;
        bool is_garbage = false;
        int nr_of_none_garbage = 0;
        while (file.get(ch)) {
            if (!is_garbage) {
                if (ch == '<') {
                    is_garbage = true;
                }
            } else {
                if (ch == '>') {
                    is_garbage = false;
                } else if (ch == '!') {
                    file.get(ch);
                } else {
                    nr_of_none_garbage++;
                }
            }
        }
        std::cout << "SOLUTION: " << nr_of_none_garbage;
    }
    return 0;
}
