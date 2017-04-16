#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork error\n");
    }
    else if(pid == 0)
    {
        printf("child %d\n", getpid());
    }
    else
    {
        printf("parent:%d\n", getpid());
        
        sleep(3000);
        assert(pid == wait(NULL));
    }

    return 0;
}
