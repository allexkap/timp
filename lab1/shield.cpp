#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>

std::error_code global_error;

void init() {
    if (system("sudo chown shield . && sudo chmod 755 .")) {
        std::cerr << "Unable to create a secure folder\n";
        return;
    }
    std::ofstream("template.tbl");
}

int check(std::string filename) {
    std::ifstream file("template.tbl");
    if (!file.is_open()) return 0;

    std::string line;
    while (std::getline(file, line))
        if (std::regex_match(filename, std::regex(line)))
            return 1;

    return 0;
}


int main(int argc, char** argv) {
    if (argc < 2) return 0;
    if (argc > 4) return 1;

    for (int i = 2; i < argc; ++i) {
        if (check(argv[i])) {
            std::cerr << "Sorry, forbidden name\n";
            return 1;
        }
    }

    switch(argv[1][0]) {
        case 'i':
            init();
            break;
        case 'e':
            std::filesystem::rename("template.tbl.bak", "template.tbl", global_error);
            break;
        case 'd':
            std::filesystem::rename("template.tbl", "template.tbl.bak", global_error);
            break;
        case 't':
            std::ofstream(argv[2], std::ios::out);
            break;
        case 'r':
            std::remove(argv[2]);
            break;
        case 'm':
            std::filesystem::rename(argv[2], argv[3], global_error);
            break;
        case 'c':
            std::filesystem::copy(argv[2], argv[3], global_error);
            break;
        default:
            return 1;
    }
    return 0;
}
