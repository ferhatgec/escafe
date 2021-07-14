#include "include/escafe.hpp"
#include <fstream>

int main() {
    std::ifstream example("example.txt");

    for(std::string temp; std::getline(example, temp); ) {
        std::cout << escafe::run(temp) << '\n';
    }
}