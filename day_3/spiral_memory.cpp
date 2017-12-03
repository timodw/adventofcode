#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define INPUT 277678

uint64_t get_ring(uint64_t);

int main() {
    uint64_t ring = get_ring(INPUT);
    uint64_t max_square = (2 * ring - 1) * (2 * ring - 1);
    uint64_t previous_end = (2 * (ring - 1) - 1) * (2 * (ring - 1) - 1);
    uint64_t size_of_ring = max_square - previous_end - 1;
    uint64_t quadrant_size = (size_of_ring + 1) / 4;
    uint64_t first_quadrant = previous_end + ring - 1;
    std::vector<uint64_t> distance_to_quadrants;
    distance_to_quadrants.push_back(INPUT - first_quadrant);
    distance_to_quadrants.push_back(INPUT - (first_quadrant + quadrant_size));
    distance_to_quadrants.push_back(INPUT - (first_quadrant + 2 * quadrant_size));
    distance_to_quadrants.push_back(INPUT - (first_quadrant + 3 * quadrant_size));
    uint64_t min_distance_to_quadrant = *min_element(distance_to_quadrants.begin(), distance_to_quadrants.end());
    std::cout << "SOLUTION: " << min_distance_to_quadrant + ring - 1;
    return 0;
}

uint64_t get_ring(uint64_t number) {
    uint64_t i = 0;
    while ((2 * i - 1) * (2 * i - 1) < number) i++;
    return i;
}
