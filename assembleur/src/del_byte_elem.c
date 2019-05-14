#include "../../includes/asm.h"

void	ft_del_byte_elem(t_bytes **list, t_bytes *elem)
{
	t_bytes	*tmp;
	t_bytes	*prev;

	tmp = *list;
	if (tmp != elem)
	{
		while (tmp->next && tmp->next != elem)
		{
//			ft_printf("tmp -> %s\n", tmp->label);
			tmp = tmp->next;
		}
		prev = tmp;
		tmp = tmp->next;
		prev->next = tmp->next;
	}
	else
		*list = (*list)->next;
	ft_strdel(&tmp->label);
	ft_memdel((void*)&tmp);
}
