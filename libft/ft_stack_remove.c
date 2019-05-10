/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:42:13 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/03 17:42:14 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Remove the node at 'index'.
*/

void	ft_stack_remove(t_stack **head, const unsigned int index)
{
	t_stack			*tmp;
	t_stack			*current;
	unsigned int	i;

	if (*head)
	{
		current = *head;
		i = 1;
		while (i < (index - 1))
		{
			current = current->next;
			i++;
		}
		tmp = current->next;
		current->next = current->next->next;
		tmp->nb = 0;
		tmp->next = NULL;
		ft_memdel((void*)&tmp);
	}
}
