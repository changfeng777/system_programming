#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void print_exit(int status)
{
    if(WIFEXITED(status))
    {
        // 子进程正常退出
        printf("nomal:%d\n",WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        // 子进程异常退出
        printf("abnormal:%d\n", WTERMSIG(status));
    }
    else if(WIFSTOPPED(status))
    {
        // 子进程暂停
        printf("child stopped:%d\n",WSTOPSIG(status));
    }
}

// 父进程以阻塞的方式等待子进程
void block()
{
    pid_t pid;

    pid = fork();
    if(pid < 0)
    {
        perror("fork failed\n");
        exit(1);
    }
    else if(pid == 0)
    {
        sleep(3);

        //exit(1); //子进程正常结束
        abort(); //子进程异常结束
    }
    else
    {
        int status;
        // 以阻塞的方式等待
        pid_t ret = waitpid(pid, &status, 0);
        assert(ret == pid);
        printf("parent %d wait child %d 3s\n",getpid(), pid);
        
        print_exit(status);
    }
}

// 父进程以非阻塞的方式等待子进程
int unblock()
{
    pid_t pid;

    pid = fork();
    if(pid < 0)
    {
        perror("fork failed\n");
        exit(1);
    }
    else if(pid == 0)
    {
        sleep(3);

        exit(1); //子进程正常结束
        //abort(); //子进程异常结束
    }
    else
    {
        int status;
        // 以阻塞的方式等待
        pid_t ret;
        
        while(1)
        {
            ret = waitpid(pid, &status, WNOHANG);
            if(ret == 0)
            {
                printf("child is not finish\n");
                sleep(1);
            }
            else if(ret == pid)
            {
                break;
            }
            else if(ret == -1)
            {
               perror("waitpid error\n"); 
            }
        }

        printf("parent %d wait child %d 3s\n",getpid(), pid);
        print_exit(status);
    }

    return 0;
}

int main()
{
    block();
    printf("---------------------------\n");
    unblock();
    return 0;
}
