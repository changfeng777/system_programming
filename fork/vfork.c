#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

void fun()
{
    printf("child exit\n");
}

int main()
{
    pid_t pid;
    pid = vfork();
    if(pid < 0)
    {
        perror("vfork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
       // atexit(fun);
        printf("child:%d\n", getpid());       
        sleep(1);
        //_exit(0);
        return 0;
    }
    else
    {           
        printf("parent:%d\n", getpid());       
    }

    return 0;
}
