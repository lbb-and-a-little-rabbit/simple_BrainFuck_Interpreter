#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BrainDuck.h"

int main() {
    std::string filename;
    std::cin >> filename;

    std::ifstream program_file(filename);
    if (!program_file.is_open()) {
        std::cerr << "Failed to open program file\n";
        return 1;
    }

    std::stringstream program_buf;
    program_buf << program_file.rdbuf();
    program_file.close();

    std::string program = program_buf.str();

    BrainDuckVM vm;
    vm.init(program);

    bool need_input = false;
    for (char c : program) {
        if (c == ',') {
            need_input = true;
            break;
        }
    }

    if (need_input) {
        std::ifstream input_file("input.fuck");
        if (!input_file.is_open()) {
            std::cerr << "Program requires input, but failed to open input.fuck\n";
            return 1;
        }
        vm.executeProgram(input_file);
        input_file.close();
    } else {
        std::stringstream empty_input;
        vm.executeProgram(empty_input);
    }

    return 0;
}
