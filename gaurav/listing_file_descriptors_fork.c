#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
        printf("Hello\n");
        execl("/bin/ls", "ls", "-l", (char*)0);
        //system("ls -l");
        printf("Hi\n");
}
