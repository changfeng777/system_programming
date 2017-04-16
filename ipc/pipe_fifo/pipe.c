#include<unistd.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

const size_t BUFFER_SIZE = 128;
int main()
{
    pid_t pid;
    int pipefd[2];
    char buffer[BUFFER_SIZE];
    int n;

    if(pipe(pipefd) == -1)
    {
        perror("pipe error\n");
        exit(-1);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        // child read
        size_t i = 0;

        // 关闭写
        close(pipefd[1]);
        
        while(i < 5)
        {
            n = read(pipefd[0],buffer,BUFFER_SIZE);
            if(n == 0)
            {
                printf("child read end\n"); 
                break;
            }
            printf("child read:%s\n", buffer);
            ++i;
        }
        
        //close(pipefd[0]);
        sleep(5);
        read(pipefd[0], buffer, BUFFER_SIZE);
        printf("child wake up read: %s\n", buffer);   
    }
    else
    {
        // parent write
        char* str = "hello child";
        size_t i = 0;

        // 关闭读
        close(pipefd[0]);

        while(i < 100000)
        {    
            sprintf(buffer, "%s:%d", str, i);
            printf("parent write:%s\n", buffer);
            write(pipefd[1], buffer, strlen(buffer));
            ++i;
            //sleep(1);
        }

        close(pipefd[1]);
        printf("parent write end\n");

        assert(wait(NULL) != -1);
    }

    return 0;
}
