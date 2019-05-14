#include "../../includes/asm.h"

t_parser	*parser_init(void)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	new->blanks = NULL;
	new->labels = NULL;
	new->line = NULL;
	new->index = 0;
	new->index_instruction = 0;
	new->err_code = 0;
	new->err_msg = NULL;
	new->fd = -1;
	return (new);
}

t_bytes		*bytes_init(t_parser *data)
{
	t_bytes	*new;

	if (!(new = (t_bytes*)malloc(sizeof(*new))))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc struct s_bytes.";
		return (NULL);
	}
	new->label = NULL;
	new->index = 0;
	new->index_instruction = 0;
	new->size = 0;
	new->next = NULL;
	return (new);
}
