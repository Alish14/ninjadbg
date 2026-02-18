#pragma once
#include <stdexcept>
#include <string>

class DebuggerError : public std::runtime_error {
public:
    explicit DebuggerError(const std::string& msg)
        : std::runtime_error(msg) {}
};
