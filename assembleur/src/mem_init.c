#include "../../includes/asm.h"

t_parser	*parser_init(void)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	new->line = NULL;
	new->index = 0;
	new->err_code = 0;
	new->err_msg = NULL;
	new->fd = -1;
	return (new);
}
