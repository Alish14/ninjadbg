#pragma once
#include "process.hpp"

class Debugger {
public:
    explicit Debugger(const std::string& program);
    void run();

private:
    Process m_process;
};
