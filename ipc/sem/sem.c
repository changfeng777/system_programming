#include"sem.h"

int main()
{
    int sem_id = create_sem(2, IPC_CREAT);
    init_sem(sem_id, 0, 1);
    init_sem(sem_id, 1, 2);
    print_sem_array(sem_id, 2);

    sem_p(sem_id, 0);
    print_sem_array(sem_id, 2);
    
    sem_v(sem_id, 1);
    print_sem_array(sem_id, 2);

    destory_sem(sem_id);
    return 0;
}
