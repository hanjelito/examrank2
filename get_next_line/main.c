#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*str;
	while ((str = get_next_line(0)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	return (0);
}
