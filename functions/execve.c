#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main()
{
	pid_t	pid;
	char	*argv[] = {"/bin/echo", "hello", NULL};
	int		val;

	pid = fork();
	if (pid == 0)
	{
		printf("Child process executes: \n");
		val = execve(argv[0], argv, NULL);
		if (val == -1)
			perror("Error");
	}
	else
	{
		wait(NULL);
		printf("Parent process sais: Done with execve\n");
	}

	return (0);
}