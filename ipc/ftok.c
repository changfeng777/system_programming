#include<stdio.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
    const char* path = "/root/install.log"; 
    key_t key = ftok(path, 0x11);
    assert(key != -1);

    struct stat st;
    int ret = stat(path, &st);
    assert(ret != -1);

    printf("st_dev:%x, st_ino:%x, key:%x\n", st.st_dev, st.st_ino, key);

    return 0;
}
