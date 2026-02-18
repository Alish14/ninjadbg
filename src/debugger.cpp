#include "debugger.hpp"
#include <iostream>

Debugger::Debugger(const std::string& program)
    : m_process(program) {}

void Debugger::run() {
    m_process.launch();
    std::cout << "Process started with PID: "
              << m_process.pid() << "\n";
}
