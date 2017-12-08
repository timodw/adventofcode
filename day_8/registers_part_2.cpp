#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>

int64_t process_line(std::string);

std::unordered_map<std::string, int64_t> registers;

int main() {
    int64_t max_value;
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        getline(file, line);
        max_value = process_line(line);
        while (getline(file, line)) {
            int64_t value = process_line(line);
            if (value > max_value) max_value = value;
        }

        std::cout << "SOLUTION: " << max_value;
    }
    return 0;
}

int64_t process_line(std::string line) {
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
    return registers[register_name];
}
