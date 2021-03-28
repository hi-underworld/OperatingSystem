#include<stdio.h>
#include<stdlib.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
 
int main()
{
        unsigned long x = 0;
        x = syscall(335);        //测试335号系统调用
        printf("systemcall result is %ld\n", x);
        return 0;
}


