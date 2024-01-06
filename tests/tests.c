
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

static bool	is_correct_pipe(char *curr, char *next)
{
	if (strlen(curr) == 1 && strchr(curr, '|'))
	{
		if (next == NULL)
			return (false);
		if (strlen(next) == 2)
		{
			if (strstr(next, "&&") || strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{
	char	*curr = argv[1];
	char	*next = argv[2];

	printf("Res = %d\n", is_correct_pipe(curr, next));
}