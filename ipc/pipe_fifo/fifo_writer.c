#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<assert.h>
#include<stdio.h>
#include<fcntl.h>

const char* fifo_path = "/tmp/myfifo"; 
int main()
{
    int ret = mkfifo(fifo_path, 0666|S_IFIFO);
    if(ret == -1 && errno != EEXIST)
    {
        perror("mkfifo errno\n");       
        return -1;
    }

    int fd = open(fifo_path, O_RDWR);
    assert(fd != -1);
    
    char buff[128];
    while(1)
    {
        printf("writer:");
        scanf("%s", buff);
        int ret = write(fd, buff, strlen(buff)+1);
        assert(ret != -1);

        if(strcmp(buff, "quit") == 0)
            break;
    }

    close(fd);
    return 0;
}
