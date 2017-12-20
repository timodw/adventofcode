#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#define ITERATIONS 10000
#define DIMENSIONS 3

class particle {
    public:
        int id;
        std::vector<int> position;
        std::vector<int> velocity;
        std::vector<int> acceleration;

        particle(int i) : id(i) {};

        void set_position(std::string);
        void set_velocity(std::string);
        void set_acceleration(std::string);
        void update();
};

struct VectorHash {
    size_t operator() (const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

auto pos_comp = [](particle o1, particle o2) {
                    return (std::abs(o1.position[0]) + std::abs(o1.position[1]) + std::abs(o1.position[2])) < (std::abs(o2.position[0]) + std::abs(o2.position[1]) + std::abs(o2.position[2]));
                };

std::vector<particle> particles;

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int id = 0;
    while (getline(file, line)) {
        particle part(id++);
        int start = 3;
        int end = line.find(">");
        part.set_position(line.substr(start, end - start));
        start = end + 6;
        end = line.find(">", start);
        part.set_velocity(line.substr(start, end - start));
        start = end + 6;
        end = line.find(">", start);
        part.set_acceleration(line.substr(start, end - start));
        particles.push_back(part);
    }
    particle* min_el = &*std::min_element(particles.begin(), particles.end(), pos_comp);
    std::unordered_set<int> removed;
    for (size_t i = 0; i < ITERATIONS; i++) {
        std::unordered_map< std::vector<int>, int, VectorHash> part_mapping;
        for (particle& part: particles) {
            part.update();
            if (part_mapping.find(part.position) != part_mapping.end()) {
                removed.insert(part_mapping[part.position]);
                removed.insert(part.id);
            } else {
                part_mapping[part.position] = part.id;
            }
            if (pos_comp(part, *min_el)) min_el = &part;
        }
    }
    std::cout << "SOLUTION: " << particles.size() - removed.size();
    return 0;
}

void particle::update() {
    for (size_t i = 0; i < DIMENSIONS; i++) {
        velocity[i] = velocity[i] + acceleration[i];
        position[i] = position[i] + velocity[i];
    }
}

void particle::set_position(std::string vec_str) {
    int start = 0;
    int end = vec_str.find(",");
    position.push_back(std::stoi(vec_str.substr(start, end++)));
    start = end;
    end = vec_str.find(",", start);
    position.push_back(std::stoi(vec_str.substr(start, end++ - start)));
    start = end;
    position.push_back(std::stoi(vec_str.substr(start)));
}

void particle::set_velocity(std::string vec_str) {
    int start = 0;
    int end = vec_str.find(",");
    velocity.push_back(std::stoi(vec_str.substr(start, end++)));
    start = end;
    end = vec_str.find(",", start);
    velocity.push_back(std::stoi(vec_str.substr(start, end++ - start)));
    start = end;
    velocity.push_back(std::stoi(vec_str.substr(start)));
}

void particle::set_acceleration(std::string vec_str) {
    int start = 0;
    int end = vec_str.find(",");
    acceleration.push_back(std::stoi(vec_str.substr(start, end++)));
    start = end;
    end = vec_str.find(",", start);
    acceleration.push_back(std::stoi(vec_str.substr(start, end++ - start)));
    start = end;
    acceleration.push_back(std::stoi(vec_str.substr(start)));
}
