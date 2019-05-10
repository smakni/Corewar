#include "../includes/asm.h"

int		main(int argc, char **argv)
{
	(void)argc;

	int	fd = open("test.cor", O_WRONLY);
	char str[3];

	int i = 1;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "sti") == 0)
			str[i - 1] = 11;
		else if (ft_strcmp(argv[i], "r1") == 0)
			str[i - 1] = 1;
		i++;
	}
	str[2] = 0;
	write(fd, str, ft_strlen(str));
	close(fd);
	return (0);
}
