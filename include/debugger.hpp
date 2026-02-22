#pragma once
#include "process.hpp"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/user.h>

class Debugger {
public:
    explicit Debugger(const std::string& program);
    void run();

private:
    void debugger_loop();
    void wait_for_signal();
    Process m_process;
};
