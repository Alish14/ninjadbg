#include "debugger.hpp"
#include <iostream>

Debugger::Debugger(const std::string& program)
    : m_process(program) {}

void Debugger::run() {
    m_process.launch();
    debugger_loop(); 
    std::cout << "Process started with PID: "
              << m_process.pid() << "\n";
}

void Debugger::debugger_loop() {
    pid_t pid = m_process.pid();

    while (true) {
        std::cout << "dbg> ";
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "cont") {
            ptrace(PTRACE_CONT, pid, nullptr, nullptr);
            wait_for_signal();
        }
        else if (cmd == "step") {
            ptrace(PTRACE_SINGLESTEP, pid, nullptr, nullptr);
            wait_for_signal();
        }
        else if (cmd == "regs") {
            user_regs_struct regs;
            ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
            std::cout << "RIP: 0x" << std::hex << regs.rip << "\n";
        }
        else if (cmd == "exit") {
            break;
        }
    }
}

void Debugger::wait_for_signal() {
    int status;
    waitpid(m_process.pid(), &status, 0);

    if (WIFSTOPPED(status)) {
        std::cout << "Child stopped by signal: "
                  << WSTOPSIG(status) << "\n";
    }
}