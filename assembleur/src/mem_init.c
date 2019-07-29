/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:45:59 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 21:51:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			parser_init(t_parser *parser, char *pathname)
{
	ft_bzero(parser, sizeof(t_parser));
	if (!(parser->bytecode = (unsigned char*)malloc(sizeof(*parser->bytecode)
						* SIZE_BUFFER)))
		return (FAIL);
	parser->nb_realloc = 1;
	parser->pathname = pathname;
	parser->nb_line = 1;
	parser->fd = -1;
	return (SUCCESS);
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
		data->err_code = 2;
		data->err_msg = "Fail to malloc.";
		return (FAIL);
	}
	ft_memcpy(data->bytecode, tmp, data->index);
	ft_memdel((void*)&tmp);
	return (SUCCESS);
}
