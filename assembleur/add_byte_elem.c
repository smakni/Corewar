/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_byte_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:21:16 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
