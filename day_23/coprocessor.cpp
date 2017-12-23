#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

int64_t get_register_value(std::string);

uint8_t pc = 0;
std::unordered_map<std::string, int64_t> registers;
std::vector<std::string> instructions;

int main() {
    registers["a"] = 1;
    registers["b"] = 84 * 100 + 100000;
    registers["c"] = registers["b"] + 17000;
    do {
        registers["f"] = 1;
        registers["e"] = 2;
        for (registers["d"] = 2; registers["d"] * registers["d"] <= registers["b"]; registers["d"] = registers["d"] + 1) {
            if((registers["b"] % registers["d"] == 0)) {
                registers["f"] = 0;
                break;
            }
        }
        if( registers["f"] == 0) {
            registers["h"] = registers["h"] + 1;
        }
        registers["g"] = registers["b"] - registers["c"];
        registers["b"] = registers["b"] + 17;
    } while (registers["g"] != 0);

    std::cout << "SOLUTION: " << registers["h"];
    return 0;
}

int64_t get_register_value(std::string reg) {
    if (registers.find(reg) != registers.end()) {
        return registers[reg];
    } else {
        return 0;
    }
}
