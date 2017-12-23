#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

void process_instruction(std::string);
int64_t get_register_value(std::string);
int64_t get_value(std::string);

uint8_t pc = 0;
int64_t nr_of_mul = 0;
std::unordered_map<std::string, int64_t> registers;
std::vector<std::string> instructions;

int main() {
    std::ifstream file("input.txt");
    std::string line;
    while (getline(file, line)) {
        instructions.push_back(line);
    }
    while (pc >= 0 && pc < instructions.size()) {
        process_instruction(instructions[pc]);
    }
    std::cout << "SOLUTION: " << nr_of_mul;
    return 0;
}

void process_instruction(std::string instruction) {
    uint8_t start = 0;
    uint8_t end = instruction.find(" ");
    std::string op = instruction.substr(0, end++);
    start = end;
    end = instruction.find(" ", start);
    std::string lhv_str = instruction.substr(start, end++ - start);
    start = end;
    std::string rhv_str = instruction.substr(start);
    int64_t rhv = get_value(rhv_str);
    if (op == "set") {
        registers[lhv_str] = rhv;
    } else if (op == "sub") {
        registers[lhv_str] = get_register_value(lhv_str) - rhv;
    } else if (op == "mul") {
        registers[lhv_str] = get_register_value(lhv_str) * rhv;
        nr_of_mul++;
    } else if (op == "jnz") {
        int64_t val = get_value(lhv_str);
        if (val != 0) {
            pc += rhv - 1;
        }
    }
    pc++;
}

int64_t get_value(std::string val_str) {
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
