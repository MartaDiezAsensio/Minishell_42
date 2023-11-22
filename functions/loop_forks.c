#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main()
{
	int		num_children;
	int		i;
	pid_t	pid;

	printf("Write how many childres processes you need:   ");
	scanf("%d", &num_children);

	i = 0;
	while (i < num_children)
	{
		pid = fork();

		if (pid == 0)
		{
			printf("Child Process %d with pid: %d\n", i + 1, getpid());
			return (0); // with execve it exits anyway
		}
		else if (pid < 0)
		{
			perror("Error when creting the child process\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < num_children)
	{
		wait(NULL);
		i++;
	}

	printf("Parent process sais all childres have finished\n");
	return (0);
}