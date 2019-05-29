/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:45:59 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/29 16:11:33 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_parser	*parser_init(char *pathname)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	ft_bzero((void*)new, sizeof(*new));
	if (!(new->bytecode = (unsigned char*)malloc(sizeof(*new->bytecode)
						* SIZE_BUFFER)))
	{
		ft_memdel((void*)&new);
		return (FAIL);
	}
	new->nb_realloc = 1;
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

int			ft_realloc_bytecode(t_parser *data)
{
	unsigned char	*tmp;

	tmp = data->bytecode;
	data->nb_realloc++;
	if (!(data->bytecode = (unsigned char*)malloc(data->nb_realloc * SIZE_BUFFER
					* sizeof(*data->bytecode))))
	{
		ft_memdel((void*)&tmp);
		return (FAIL);
	}
	ft_memcpy(data->bytecode, tmp, data->index);
	ft_memdel((void*)&tmp);
	return (SUCCESS);
}
