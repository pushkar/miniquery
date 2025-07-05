#include <iostream>
#include "query_executor.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./engine <arrow-ipc-file> <query>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string query = argv[2];

    try {
        QueryExecutor::Run(filename, query);
    } catch (const std::exception& e) {
        std::cerr << "Query error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}