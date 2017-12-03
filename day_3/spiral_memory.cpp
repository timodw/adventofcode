#include <iostream>

#define INPUT 277678

uint64_t* grid;
int64_t mat_size = 526;

uint64_t sum_neighbours(uint64_t, uint64_t);

int main() {
    grid = new uint64_t[INPUT];
    int64_t x = mat_size / 2;
    int64_t y = mat_size / 2;
    uint8_t edge = 0; //0: Right, 1: Top, 2: Left, 3: Bottom
    uint64_t edge_size = 2;
    uint64_t pos_on_edge = 1;
    grid[x++ * mat_size + y] = 1;
    for (;;) {
        grid[x * mat_size + y] = sum_neighbours(x, y);
        if (grid[x * mat_size + y] > INPUT) break;
        if (edge == 3 && pos_on_edge == edge_size) {
            edge_size += 2;
            x++;
            edge = 0;
            pos_on_edge = 1;
            continue;
        }
        if (pos_on_edge == edge_size) {
            edge = ++edge % 4;
            pos_on_edge = 1;
        } else {
            pos_on_edge++;
        }
        switch (edge) {
            case 0:
                y++;
                break;
            case 1:
                x--;
                break;
            case 2:
                y--;
                break;
            case 3:
                x++;
        }
    }  
    std::cout << "SOLUTION: " << grid[x * mat_size + y];
    delete[] grid;
    return 0;
}

uint64_t sum_neighbours(uint64_t x, uint64_t y) {
    uint64_t sum = 0;
    sum += grid[x * mat_size + y + 1];
    sum += grid[(x + 1) * mat_size + y];
    sum += grid[(x + 1) * mat_size + y + 1];
    sum += grid[x * mat_size + y - 1];
    sum += grid[(x - 1) * mat_size + y];
    sum += grid[(x - 1) * mat_size + y - 1];
    sum += grid[(x + 1) * mat_size + y - 1];
    sum += grid[(x - 1) * mat_size + y + 1];
    return sum;
}
