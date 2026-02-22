#include "debugger.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./mini_dbg <program>\n";
        return 1;
    }

    Debugger dbg(argv[1]);
    dbg.run();
    
}
