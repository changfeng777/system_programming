#pragma once

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

const char* PATH = "/tmp";
const int ID = 0x1234;

union semun
{
   int  val;                /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

static int create_sem(int sem_num, int sem_flg)
{
    key_t key = ftok(PATH, ID);
    int sem_id = semget(key, sem_num, sem_flg);
    assert(sem_id != -1);

    return sem_id;
}

static void init_sem(int sem_id, int which, int val)
{
    union semun s;
    s.val = val;
    int ret = semctl(sem_id, which, SETVAL, s);
    assert(ret != -1);
}

static void sem_p(int sem_id, int which)
{
    struct sembuf buf;
    memset(&buf, 0, sizeof(struct sembuf));
    buf.sem_op = -1;
    buf.sem_flg = 0;
    buf.sem_num = which;

    int ret = semop(sem_id, &buf, 2);
    assert(ret != -1);
}

static void sem_v(int sem_id, int which)
{
    struct sembuf buf;
    memset(&buf, 0, sizeof(struct sembuf));
    buf.sem_op = 1;
    buf.sem_flg = 0;
    buf.sem_num = which;
    int ret = semop(sem_id, &buf, 2);
    assert(ret != -1);
}

static void destory_sem(int sem_id)
{
   int ret = semctl(sem_id, 0, IPC_RMID);
   assert(ret != -1);
}

static void print_sem_array(int sem_id, int sem_num)
{
    union semun s;   
    s.array = (unsigned short*)malloc(sizeof(unsigned short)*sem_num);
    assert(s.array);
    
    int ret = semctl(sem_id, 0, GETALL, s);
    assert(ret != -1);
    int i = 0;
    while(i < sem_num)
    {
        printf("sem[%d]:%d ", i, s.array[i]);
        ++i;
    }
    printf("\n");  

    free(s.array);
}
