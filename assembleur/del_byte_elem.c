/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_byte_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:21:06 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_del_byte_elem(t_bytes **list, t_bytes *elem)
{
	t_bytes	*tmp;
	t_bytes	*prev;

	tmp = *list;
	if (tmp != elem)
	{
		while (tmp->next && tmp->next != elem)
			tmp = tmp->next;
		prev = tmp;
		tmp = tmp->next;
		prev->next = tmp->next;
	}
	else
		*list = (*list)->next;
	ft_strdel(&tmp->label);
	ft_memdel((void*)&tmp);
}
