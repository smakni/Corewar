#include "../includes/asm.h"

int		main(int argc, char **argv)
{
	(void)argc;

	int	fd = open("test.cor", O_WRONLY);
	// ft_dprintf(fd, "\\x%c\\x%s", 'b', "68");
	// write(fd, (void*)13, 4);
	char str[2];
	if (ft_strcmp(argv[1], "sti") == 0)
		ft_sprintf(str, "%c", 13);
		// write(fd, "\xb", 1);
	if (ft_strcmp(argv[2], "r1") == 0)
		ft_sprintf(str, "%c", 1);
		// write(fd, 1, 1);
	write(fd, str, 2);
	close(fd);
	return (0);
}
