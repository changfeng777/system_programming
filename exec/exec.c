#include<stdio.h>
#include<unistd.h>

int main()
{
    char* path[]={"PATH=/home/xjh",NULL};
    
    char* const ps_argv[] ={"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
    char* const ps_envp[] ={"PATH=/bin:/usr/bin", NULL}; 

   //execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);

   //execv("/bin/ps", ps_argv);

   //execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);

   //execve("/bin/ps", ps_argv, ps_envp);

   //execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);

   //execvp("ps", ps_argv);
    
    execl("/home/xjh/print_argv", "print_argv", "arg1", "arg2", NULL);

    // 运行到这里则说明exec系列的函数调用失败了。
    perror("exec error\n");
    return 0;
}
