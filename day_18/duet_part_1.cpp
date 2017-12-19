#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> instructions;
std::unordered_map<std::string, int64_t> registers;
int64_t last_played_frequency;
int64_t pc = 0;
bool recover = false;

void process_line(std::string);
int64_t get_instruction_value(std::string);
int64_t get_register_value(std::string);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) instructions.push_back(line);
    while (!recover) {
        process_line(instructions[pc]);
    }
    std::cout << "SOLUTION: " << last_played_frequency;
    return 0;
}

void process_line(std::string line) {
    int64_t start = 0;
    int64_t end = line.find(" ");
    std::string instr = line.substr(0, end);
    start = ++end;
    end = line.find(" ", start);
    std::string reg = line.substr(start, end - start);
    if (instr == "snd") {
        last_played_frequency = get_register_value(reg);
    } else if (instr == "set") {
        int64_t val = get_instruction_value(line);
        registers[reg] = val;
    } else if (instr == "add") {
        int64_t val = get_instruction_value(line);
        registers[reg] = get_register_value(reg) + val;
    } else if (instr == "mul") {
        int64_t val = get_instruction_value(line);
        registers[reg] = get_register_value(reg) * val;       
    } else if (instr == "mod") {
        int64_t val = get_instruction_value(line);
        registers[reg] = get_register_value(reg) % val;
    } else if (instr == "rcv") {
        if (get_register_value(reg) != 0) recover = true;
    } else if (instr == "jgz") {
        int64_t val = get_instruction_value(line);
        if (get_register_value(reg) > 0) {
            pc += val - 1;   
        }
    }
    pc++;
}

int64_t get_instruction_value(std::string instr) {
    std::string val_str = instr.substr(instr.find_last_of(" ") + 1);
    if (val_str[0] < 'a') {
        return std::stoi(val_str);
    } else {
        return get_register_value(val_str);
    }
}

int64_t get_register_value(std::string reg) {
    if (registers.find(reg) != registers.end()) {
        return registers[reg];
    } else {
        return 0;
    }
}
