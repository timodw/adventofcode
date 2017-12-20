#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define ITERATIONS 10000
#define DIMENSIONS 3

class particle {
    public:
        int id;
        std::vector<int64_t> position;
        std::vector<int64_t> velocity;
        std::vector<int64_t> acceleration;

        particle(int i) : id(i) {};

        void set_position(std::string);
        void set_velocity(std::string);
        void set_acceleration(std::string);
        void update();
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
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (particle& part: particles) {
            part.update();
            if (pos_comp(part, *min_el)) min_el = &part;
        }
    }
    std::cout << "SOLUTION: " << min_el->id;
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
