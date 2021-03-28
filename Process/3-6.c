#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
 int main() {
     pid_t pid ;
     int num, tmp;
     int first = 0;
     int second = 1;
     printf("please input the number:");
     scanf("%d", &num);
     pid = fork();
     if (pid < 0) {
         printf("fork error\n");
         return -1;
     } else if (pid == 0){
         printf("the fib array is :\n");
         while(num > 0){
             printf("%d ", first);
             tmp = first;
             first = second;
             second = tmp + second;
             num --;
         }
     } else {
         wait(NULL);
         printf("done\n");
     }
     return 0;
 }