#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

std::unordered_map< int, std::unordered_set<int> > sets;

void process_line(std::string);
int get_solution();

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            process_line(line);
        }
    }
    std::cout << "SOLUTION: " << get_solution();
    return 0;
}

void process_line(std::string line) {
    int start = 0;
    int end = line.find(" ");
    int proc_id = std::stoi(line.substr(start, end - start));
    start = end + 5;
    end = line.find(",", start);
    while (end != std::string::npos) {
             sets[proc_id].insert(std::stoi(line.substr(start, end - start)));
             start = end + 2;
             end = line.find(",", start);
    }
    sets[proc_id].insert(std::stoi(line.substr(start)));
}

int get_solution() {
    std::unordered_set<int> to_visit = sets[0];
    std::unordered_set<int> visited;
    visited.insert(0);
    while (!to_visit.empty()) {
        for (int proc: to_visit) {
            for (int pipe: sets[proc]) {
                sets[0].insert(pipe);
                if (visited.find(pipe) == visited.end()) {
                    to_visit.insert(pipe);
                }
            }
            visited.insert(proc);
            to_visit.erase(proc);
        }
    }
    return sets[0].size();
}
