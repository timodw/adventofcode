#include <iostream>
#include <fstream>
#include <string>

#define SIZE 1000
#define ITERATIONS 10000

void burst();

char grid[SIZE][SIZE];
int x = (SIZE / 2 - 25 / 2) + 12;
int y = (SIZE / 2 - 25 / 2) + 12;
int infected_bursts = 0;
int dir = 1; //0 = LEFT; 1 = UP; 2 = RIGHT; 3 = DOWN


int main() {
    std::ifstream file("input.txt");
    std::string line;
    size_t i = 0;
    while (getline(file, line)) {
        size_t j = 0;
        for (char ch: line) {
            grid[(SIZE / 2 - line.size() / 2) + i][(SIZE / 2 - line.size() / 2) + j++] = ch;
        }
        i++;
    }

    for (size_t i = 0; i < ITERATIONS; i++) {
        burst();
    }

    std::cout << "SOLUTION: " << infected_bursts;
    return 0;
}

void burst() {
    if (grid[x][y] == '#') {
        dir = (dir + 1) % 4;
        grid[x][y] = '.';
    } else {
        dir = ((dir - 1) + 4) % 4;
        grid[x][y] = '#';
        infected_bursts++;
    }
    switch (dir) {
        case 0:
            y--;
            break;
        case 1:
            x--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x++;
            break;
    }
}
