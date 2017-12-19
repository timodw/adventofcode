#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum direction {UP, DOWN, LEFT, RIGHT};

void move();

std::pair<int, int> position(0, 1);
std::vector< std::vector<char> > grid;
std::string letters = "";
bool done = false;
direction dir = DOWN;

int main() {
    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) {
        grid.push_back(std::vector<char>(line.begin(), line.end()));
    }
    while (!done) move();
    std::cout << letters;
    return 0;
}

void move() {
    switch (dir) {
        case UP:
            position.first--;
            break;
        case DOWN:
            position.first++;
            break;
        case LEFT:
            position.second--;
            break;
        case RIGHT:
            position.second++;
            break;
    }
    char ch = grid[position.first][position.second];
    if (ch >= 65 && ch <= 90) {
        letters += ch;
    } else if (ch == '+') {
        switch (dir) {
            case UP:
                if (position.second + 1 < grid[position.first].size() && grid[position.first][position.second + 1] != ' ') {
                    dir = RIGHT;
                } else {
                    dir = LEFT;
                }
                break;
            case DOWN:
                if (position.second + 1 < grid[position.first].size() && grid[position.first][position.second + 1] != ' ') {
                    dir = RIGHT;
                } else {
                    dir = LEFT;
                }
                break;
            case LEFT:
                if (position.first + 1 < grid.size() && grid[position.first + 1][position.second] != ' ') {
                    dir = DOWN;
                } else {
                    dir = UP;
                }
                break;
            case RIGHT:
                if (position.first + 1 < grid.size() && grid[position.first + 1][position.second] != ' ') {
                    dir = DOWN;
                } else {
                    dir = UP;
                }
                break;
        }
    }
    done = (ch == 'S');
}
