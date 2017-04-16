#include "common.h"

int main()
{
    // 获取键值和msg_id
    key_t key = ftok(FILE_PATH, ID);
    assert(key != -1);

    int msg_id = msgget(key, IPC_CREAT);
    assert(msg_id != -1);

    struct msgbuf buf;
    while(1)
    {
        // 接收客户端的消息
        int ret = msgrcv(msg_id, &buf, sizeof(buf), client_msg_type, 0);
        assert(ret != -1);
        printf("client reply:%s", buf.mtext);

        // 从终端获取消息发送给客户端
        printf("server:>");
        fgets(buf.mtext, sizeof(buf.mtext), stdin);
        if(strncmp(buf.mtext, "quit", 4) == 0)
            break;

        buf.mtype = server_msg_type;
        ret = msgsnd(msg_id, &buf, sizeof(buf), 0);
        assert(ret != -1);
    }
    
    // 服务器退出时删除消息队列
    int ret =  msgctl(msg_id, IPC_RMID, 0);
    assert(ret != -1);
       
    return 0;
}
