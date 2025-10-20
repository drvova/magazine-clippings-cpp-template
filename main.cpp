#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "src/magazine_clippings.hpp"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::string othello = readFile("plays/othello.txt");
    std::string romeo = readFile("plays/romeo_and_juliet.txt");

    if (othello.empty() || romeo.empty()) {
        std::cout << "Error loading files" << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    bool result = canCreateNote(romeo, {othello});
    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Can create Romeo and Juliet from Othello? " << (result ? "YES" : "NO") << std::endl;
    std::cout << "Time: " << time.count() << " microseconds" << std::endl;

    return 0;
}
