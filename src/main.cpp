#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sstream>
#include "inputHandle.h"

std::vector<std::string> parser(std::string s){
  std::vector<std::string> out{};
  std::stringstream ss(s);
  std::string item;

  while(std::getline(ss,item)){
    out.push_back(item);
  }

  return out;
}


int main()
{
  int status;
  long orig_eax;

  pid_t pid=fork();

  if(pid == 0){

    ptrace(PTRACE_TRACEME,0,NULL,NULL);
    execl("/bin/ls","ls",NULL);
    perror("execl failed");
    exit(1);
    std::cout << "printed from child process " << getpid() <<std::endl;

  }
  else
  {
        int status;

        wait(&status);

        if(WIFSTOPPED(status)){

          struct user_regs_struct regs;

          ptrace(PTRACE_GETREGS,pid,NULL,&regs);


          #if defined(__x86_64__)
            long syscall_number = regs.orig_rax;
            printf("System call: %ld\n",syscall_number);
          #elif defined(__i386__)
            long syscall_number = regs.orig_eax;
            printf("System call: %ld\n", syscall_number);
          #endif

        }
        wait(NULL);
    }
  return 0;
}
