#include "../../includes/asm.h"

void	ft_add_byte_elem(t_bytes **list, t_bytes *elem)
{
	if (*list)
	{
		elem->next = *list;
		*list = elem;
	}
	else
		*list = elem;
}
