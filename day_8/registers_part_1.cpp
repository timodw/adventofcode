#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>

void process_line(std::string);

std::unordered_map<std::string, int64_t> registers;
int64_t get_max_value();

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            process_line(line);
        }

        std::cout << "SOLUTION: " << get_max_value();
    }
    return 0;
}

void process_line(std::string line) {
    int end = line.find(" ");
    std::string register_name = line.substr(0, end);
    int start = end + 1;
    end = line.find(" ", start);
    std::string instruction = line.substr(start, end - start); 
    start = end + 1;
    end = line.find(" ", start);
    int64_t value = atoi(line.substr(start, end - start).c_str());
    start = end + 4;
    end = line.find(" ", start);
    std::string cond_register = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    std::string condition = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    int64_t cond_value = atoi(line.substr(start).c_str());

    if (registers.find(register_name) == registers.end()) {
        registers[register_name] = 0;
    }
    if (registers.find(cond_register) == registers.end()) {
        registers[cond_register] = 0;
    }
    
    if (instruction == "dec") value = -value;
    
    if (condition == "==") {
        if (registers[cond_register] == cond_value) 
            registers[register_name] += value;
    } else if (condition == "!=") {
        if (registers[cond_register] != cond_value) 
            registers[register_name] += value;
    } else if (condition == "<") {
        if (registers[cond_register] < cond_value) 
            registers[register_name] += value;
    } else if (condition == ">") {
        if (registers[cond_register] > cond_value) 
            registers[register_name] += value;
    } else if (condition == "<=") {
        if (registers[cond_register] <= cond_value) 
            registers[register_name] += value;
    } else if (condition == ">=") {
        if (registers[cond_register] >= cond_value) 
            registers[register_name] += value;
    }
}

int64_t get_max_value() {
    return std::max_element(
                registers.begin(),
                registers.end(),
                [] (const std::pair<std::string, int64_t>& p1, const std::pair<std::string, int64_t>& p2) {
                    return p1.second < p2.second;
                }
            )->second;
}
