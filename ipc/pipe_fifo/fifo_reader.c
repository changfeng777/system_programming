#include<string.h>
#include<sys/stat.h>
#include<assert.h>
#include<stdio.h>
#include<fcntl.h>

const char* fifo_path = "/tmp/myfifo"; 
int main()
{
    int fd = open(fifo_path, O_RDWR);
    assert(fd != -1);
    
    char buff[128];
    while(1)
    {
        int ret = read(fd, buff, sizeof(buff));
        if(ret <= 0)
        {
            printf("read error or read end of file\n");
            break;
        }
        buff[ret] = '\0';
        printf("reader:%s\n", buff);

        if(strcmp(buff, "quit") == 0)
            break;
    }

    close(fd);

    return 0;
}
