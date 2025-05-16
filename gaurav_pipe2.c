#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>

void convert(char *str);

int main()
{
	int fd1[2];
	int fd2[2];
	char buff[10];
	char buff3[10];
	pid_t x;

	pipe(fd1);
	pipe(fd2);

	x = fork();

	if (x==0)
	{
		close(fd1[1]);
		read(fd1[0], buff, 6);
		convert(buff);
		close(fd1[0]);

		close(fd2[0]);
		write(fd2[1], buff, 6);
		close(fd2[1]);
	}
	else
	{
		close(fd1[0]);
		write(fd1[1], "Hello", 6);
		close(fd1[1]);

		close(fd2[1]);
		read(fd2[0], buff3, 6);
		printf("msg=%s\n", buff3);
	}

return 0;
}

void convert(char *str)
{
	while (*str != '\0')
	{
		*str = toupper(*str);
		str++;
	}
}
