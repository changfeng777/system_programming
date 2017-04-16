#include"common.h"

int main()
{
    // 获取键值和msg_id 
    key_t key = ftok(FILE_PATH, ID);
    assert(key != -1);

    int msg_id = msgget(key, 0);
    assert(msg_id != -1);

    struct msgbuf buf;
    while(1)
    {
        // 从终端输入消息发送给服务器
        printf("client:>");
        fgets(buf.mtext, sizeof(buf.mtext), stdin);
        if(strncmp(buf.mtext, "quit", 4) == 0)
            break;

        buf.mtype = client_msg_type;
        int ret = msgsnd(msg_id, &buf, sizeof(buf), 0);
        assert(ret != -1);

        // 从服务器获取回复消息
        ret = msgrcv(msg_id, &buf, sizeof(buf), server_msg_type,0);
        assert(ret != -1);
        printf("server reply:%s", buf.mtext);
    }
}
