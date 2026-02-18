#include "process.hpp"
#include "error.hpp"
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

Process::Process(const std::string& path)
    : m_path(path) {}

void Process::launch() {
    m_pid = fork();

    if (m_pid == 0) {
        // child
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(m_path.c_str(), m_path.c_str(), nullptr);
    } else if (m_pid > 0) {
        // parent
        int status;
        waitpid(m_pid, &status, 0);
    } else {
        throw DebuggerError("fork failed");
    }
}

pid_t Process::pid() const noexcept {
    return m_pid;
}
