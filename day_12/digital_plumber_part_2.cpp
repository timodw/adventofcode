#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

typedef struct el_str {
    el_str* parent;
    int value;
} element;

std::unordered_map< int, std::unordered_set<int> > sets;
std::unordered_map<int, element*> processes;

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
    processes[proc_id] = new element {nullptr, proc_id};
}

int get_solution() {
    std::unordered_set<int> roots;
    for (auto it: sets) {
        int proc_id = it.first;
        element* proc_node = processes[proc_id];
        while (proc_node->parent != nullptr) {
            proc_node = proc_node->parent;
        }
        for (int pipe: it.second) {
            element* node = processes[pipe];
            while (node->parent != nullptr) {
                node = node->parent;
            }
            if (pipe != proc_node->value) {
                node->parent = proc_node;
            }
            if (roots.find(node->value) != roots.end()) {
                roots.erase(node->value);
            }
            roots.insert(proc_node->value);
        }
    }
    return roots.size();
}
