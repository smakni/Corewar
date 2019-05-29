/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:51:26 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/29 15:51:33 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static t_bytes	*search_data(t_bytes *list, const char *data_ref)
{
	while (list)
	{
		if (ft_strcmp(list->label, data_ref) == IDENTICAL)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void			ft_fill_addr(t_parser *data)
{
	t_bytes	*tmp;
	int		replace;

	while (data->labels)
	{
		while ((tmp = search_data(data->blanks, data->labels->label)))
		{
			replace = data->labels->index - tmp->index_instruction;
			if (tmp->size == 4)
			{
				data->bytecode[tmp->index] = replace >> 24;
				data->bytecode[tmp->index + 1] = replace >> 16;
				data->bytecode[tmp->index + 2] = replace >> 8;
				data->bytecode[tmp->index + 3] = replace;
			}
			if (tmp->size == 2)
			{
				data->bytecode[tmp->index] = replace >> 8;
				data->bytecode[tmp->index + 1] = replace;
			}
			ft_del_byte_elem(&data->blanks, tmp);
		}
		ft_del_byte_elem(&data->labels, data->labels);
	}
}
