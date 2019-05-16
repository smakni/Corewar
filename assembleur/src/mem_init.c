#include "../../includes/asm.h"

t_parser	*parser_init(char *pathname)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	ft_bzero((void*)new, sizeof(*new));
	new->pathname = pathname;
	new->nb_line = 1;
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
	ft_bzero((void*)new, sizeof(*new));
	return (new);
}

void		ft_bytesdel(t_bytes **list)
{
	t_bytes	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_strdel(&(*list)->label);
		ft_memdel((void*)&(*list));
		*list = tmp;
	}
	*list = NULL;
}
