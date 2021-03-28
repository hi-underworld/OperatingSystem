#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_SEQUENCE 10

typedef struct {
    long fib_sequence[MAX_SEQUENCE];
    int sequence_size;
} shared_data;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage : %s size\n", argv[0]);
        exit(0);
    }

    int size = atoi(argv[1]);
    if (size > MAX_SEQUENCE || size <= 0) {
        fprintf(stderr, "error: the length is a wrong value\n");
        exit(0);
    }

    shared_data * data;

    int shm_id;
    char * shared_memory;
    shm_id = shmget(IPC_PRIVATE, 4096, IPC_CREAT |  IPC_EXCL | S_IRUSR | S_IWUSR);
    printf("%d\n", shm_id);
    data = (shared_data*)shmat(shm_id, 0, 0);
    data->sequence_size = size;
    //shmdt(data);

    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork error\n");
        return -1;
    } else if (pid == 0) {
        data = (shared_data*)shmat(shm_id, 0, 0);
        data->fib_sequence[0] = 0;
        data->fib_sequence[1] = 1;
        for (int i = 2; i < data->sequence_size ; ++i) {
            data->fib_sequence[i] = data->fib_sequence[i - 1] + data->fib_sequence[i - 2];
        }
        //shmdt(data);
        //exit(0);
    } else {
        wait(NULL);
        data = (shared_data*)shmat(shm_id, 0, 0);
        for ( int i = 0; i < data->sequence_size; ++i) {
            printf("%ld ",data->fib_sequence[i]);
        }
    }
    shmdt(data);
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}