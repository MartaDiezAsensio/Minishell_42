#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t	pid;
	int		num = 0;

	printf("Before a fork num = %d\n", num);

	pid = fork();

	if (pid == -1)
	{
		perror("Unsuccesful\n");
		return 1;
	}
	if (pid == 0)
	{
		num += 100;
		printf("I am a parent process num = %d\n", num);
	}
	else 
	{
		num += 10;
		printf("I am a child process num = %d\n", num);
	}

	printf("After a fork num = %d\n", num);
}
