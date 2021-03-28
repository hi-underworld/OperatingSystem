#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
 int main(){
	 int shm_id;
	 char * shared_memory;
	 const int size = 4096;
	 pid_t pid;
	 printf("hello underworld\n");
	 shm_id = shmget(IPC_PRIVATE, 0x6400, IPC_CREAT |  IPC_EXCL | S_IRUSR | S_IWUSR);
	 if (shm_id < 0) {
		 printf("get the shared memory error\n");
	 } else {
		 printf("the shared memory 's shmid is %d\n", shm_id);
		 shared_memory = (char *) shmat(shm_id, 0, 0);
		 printf(" the shared memory is attached at the address %p\n", shared_memory);
	 }
	 pid = fork();
	 if (pid == 0){
		shared_memory = (char *) shmat (shm_id, NULL, 0);
		sprintf(shared_memory, "this is a child process\n");
		//printf("%s", shared_memory);
		shmdt(shared_memory);
	 } else if( pid > 0) {
		 wait(NULL);
		 shared_memory = (char* ) shmat (shm_id, NULL, 0);
		 // sprintf( shared_memory, "this is a parent process\n");
		 printf("%s", shared_memory);
		 shmdt(shared_memory);
	 } else{
		 printf("fork error\n");
		 return -1;
	 }
	 return 0;
 }
