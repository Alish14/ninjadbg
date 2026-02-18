#pragma once
#include <sys/types.h>
#include <string>

class Process {
public:
    explicit Process(const std::string& path);
    void launch();
    pid_t pid() const noexcept;

private:
    std::string m_path;
    pid_t m_pid = -1;
};
