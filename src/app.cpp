#include "core/processor.h"
#include <iostream>

void ParseForFilters(std::vector<std::unique_ptr<Filter>>& filters, char* arr[], int n) {
    int ind = 0;
    while (ind < n) {
        if (arr[ind][0] != '-') {
            throw std::runtime_error("Invalid arguments\n");
        }
        std::vector<std::string> args;
        args.push_back(arr[ind]);
        ind++;
        while (ind < n) {
            if (arr[ind][0] == '-') break;
            args.push_back(arr[ind]);
            ind++;
        }
        try {
            filters.push_back(Filter::IdentifyFilter(args));
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Invalid arguments: \n\t") + e.what());
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "\033[1;31mERROR:\033[0m Too few arguments" << std::endl;
        return -1;
    }
    std::string input_file_path = argv[1];
    std::string output_file_path = argv[2];
    std::vector<std::unique_ptr<Filter>> filters;
    try {
        ParseForFilters(filters, argv + 3, argc - 3);
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mERROR:\033[0m\n\t" << e.what() << std::endl;
        return -1;
    }
    try {
        Processor app(
            input_file_path,
            output_file_path,
            filters
        );
        app.MakeProcess();
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mERROR:\033[0m\n\t" << e.what() << std::endl;
        return -1;
    }
    std::cerr << "\033[1;32mSUCCESSFULLY PROCESSED\033[0m\n";
    return 0;
}
