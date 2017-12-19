#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

std::vector<std::string> instruction_list;
std::unordered_map<std::string, int64_t> registers_1;
std::unordered_map<std::string, int64_t> registers_2;
std::queue<int64_t> send_queue_1;
std::queue<int64_t> send_queue_2;
int64_t nr_of_sends = 0;
int64_t pc_1 = 0;
int64_t pc_2 = 0;
bool proc_1_waiting = false;
bool proc_2_waiting = false;

void process_instruction(bool, std::unordered_map<std::string, int64_t>&, std::queue<int64_t>&, std::queue<int64_t>&, int64_t&, std::string);
int64_t get_instruction_value(std::unordered_map<std::string, int64_t>&, std::string);
int64_t get_register_value(std::unordered_map<std::string, int64_t>&, std::string);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    registers_1["p"] = 0;
    registers_2["p"] = 1;
    while (getline(file, line)) {
        instruction_list.push_back(line);
    }
    while (pc_1 >= 0 && pc_2 >= 0 && pc_1 < instruction_list.size() && pc_2 < instruction_list.size() && !(proc_1_waiting && proc_2_waiting)) {
        process_instruction(true, registers_1, send_queue_1, send_queue_2, pc_1, instruction_list[pc_1]);
        process_instruction(false, registers_2, send_queue_2, send_queue_1, pc_2, instruction_list[pc_2]);
    }
    std::cout << "SOLUTION: " << nr_of_sends;
    return 0;
}

void process_instruction(bool proc_1, std::unordered_map<std::string, int64_t> &register_file, std::queue<int64_t> &send_queue, std::queue<int64_t> &receive_queue, int64_t &pc, std::string line) {
    int64_t start = 0;
    int64_t end = line.find(" ");
    std::string instr = line.substr(0, end);
    start = ++end;
    end = line.find(" ", start);
    std::string reg = line.substr(start, end - start);
    if (instr == "snd") {
        if (proc_1) nr_of_sends++;
        send_queue.push(get_register_value(register_file, reg));
        pc++;
    } else if (instr == "set") {
        int64_t val = get_instruction_value(register_file, line);
        register_file[reg] = val;
        pc++;
    } else if (instr == "add") {
        int64_t val = get_instruction_value(register_file, line);
        register_file[reg] = get_register_value(register_file, reg) + val;
        pc++;
    } else if (instr == "mul") {
        int64_t val = get_instruction_value(register_file, line);
        register_file[reg] = get_register_value(register_file, reg) * val;
        pc++;
    } else if (instr == "mod") {
        int64_t val = get_instruction_value(register_file, line);
        register_file[reg] = get_register_value(register_file, reg) % val;
        pc++;
    } else if (instr == "rcv") {
        if (receive_queue.size() > 0) {
            if (proc_1) {
                proc_1_waiting = false;
            } else {
                proc_2_waiting = false;
            }
            register_file[reg] = receive_queue.front();
            receive_queue.pop();
            pc++;
        } else {
            if (proc_1) {
                proc_1_waiting = true;
            } else {
                proc_2_waiting = true;
            }
        }
    } else if (instr == "jgz") {
        int64_t val = get_instruction_value(register_file, line);
        if (get_register_value(register_file, reg) > 0) {
            pc += val;
        } else {
            pc++;
        }
    }
}

int64_t get_instruction_value(std::unordered_map<std::string, int64_t>& registers, std::string instr) {
    std::string val_str = instr.substr(instr.find_last_of(" ") + 1);
    if (val_str[0] < 'a') {
        return std::stoi(val_str);
    } else {
        return get_register_value(registers, val_str);
    }
}

int64_t get_register_value(std::unordered_map<std::string, int64_t>& registers, std::string reg) {
    if (registers.find(reg) != registers.end()) {
        return registers[reg];
    } else {
        return 0;
    }
}
