#include "../includes/asm.h"

int	main(void)
{
	t_rex	*parser;

	if (!(parser = rex_init(file)))
	if (!(ft_encode_cmd("sti r1,13,%1", &index)))
		ft_printf("ERROR\n");
	else
		write(1, bytecode, index);
	return (0);
}
