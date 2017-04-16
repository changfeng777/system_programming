#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 1024
const char* FILE_PATH = "/tmp/.msg";
const size_t ID = 0;
long client_msg_type = 1;
long server_msg_type = 2;

struct msgbuf
{
    long mtype;
    char mtext[MSG_SIZE];
};
