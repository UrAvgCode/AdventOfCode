// --- Day 14: Docking Data ---

#include "benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using Memory = std::unordered_map<std::uint64_t, std::uint64_t>;
using Program = std::vector<std::pair<std::string, Memory>>;

Program parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::string mask;
    Memory memory;
    Program initialization_program;
    for (std::string line; std::getline(file, line);) {
        if (line.substr(0, 4) == "mask") {
            if (!memory.empty()) {
                initialization_program.emplace_back(mask, memory);
                memory = Memory();
            }
            mask = line.substr(7);
        } else {
            auto equals_index = line.find('=');
            auto address = std::stoull(line.substr(4, equals_index - 6));
            auto value = std::stoull(line.substr(equals_index + 2));
            memory[address] = value;
        }
    }
    initialization_program.emplace_back(mask, memory);

    return initialization_program;
}

std::uint64_t part_one(const Program &initialization_program) {
    Memory computer_memory;
    for (auto &[mask, memory]: initialization_program) {
        std::uint64_t and_mask = std::numeric_limits<std::uint64_t>::max();
        std::uint64_t or_mask = 0;
        std::uint64_t bit_mask = 1ull << 36;

        for (auto bit: mask) {
            bit_mask >>= 1;
            if (bit == '1') {
                or_mask |= bit_mask;
            } else if (bit == '0') {
                and_mask &= ~bit_mask;
            }
        }

        for (auto &[address, value]: memory) {
            computer_memory[address] = value & and_mask | or_mask;
        }
    }

    std::uint64_t sum_of_all_values = 0;
    for (auto &[_, value]: computer_memory) {
        sum_of_all_values += value;
    }

    return sum_of_all_values;
}

int main() {
    std::string filename = "../../input/2020/day_14/input.txt";
    auto initialization_program = parse_file(filename);

    std::cout << "--- Day 14: Docking Data ---" << std::endl;

    auto start = benchmark::start();
    std::cout << "\nPart 1: " << part_one(initialization_program) << std::endl;
    benchmark::end(start);

    return 0;
}
