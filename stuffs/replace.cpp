#include <iostream>
#include <fstream>
#include <string>

void replace_all(std::string &line, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while ((start_pos = line.find(from, start_pos)) != std::string::npos) {
        line.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

int main() {
    std::ifstream infile("list.txt");
    std::ofstream outfile("output.txt");

    if (!infile.is_open()) {
        std::cerr << "Cannot open list.txt\n";
        return 1;
    }

    std::string line;

    while (std::getline(infile, line)) {
        replace_all(line, "%20", " ");
        outfile << line << "\n";
    }

    infile.close();
    outfile.close();

    std::cout << "Done. Output saved to output.txt\n";
    return 0;
}

