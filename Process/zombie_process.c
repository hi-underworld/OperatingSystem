#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>
 
int main()
{
	pid_t pid=fork();
 
	if(pid==0)  //子进程
	{
     	printf("child id is %d\n",getpid());
		printf("parent id is %d\n",getppid());
	}
	else  //父进程不退出，使子进程成为僵尸进程
	{
        while(1)
		{}
	}
	exit(0);
}
