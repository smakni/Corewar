#include "../includes/asm.h"

t_rex	*rex_init(char **str)
{
	t_rex	*dino;

	if (!(dino = (t_rex*)malloc(sizeof(*dino))))
		return (NULL);
	dino->str = str;
	dino->index = 0;
	dino->error = 0;
	return (dino);
}
