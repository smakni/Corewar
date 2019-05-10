/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:45 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:46 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Rotate all elements of the stack to the top position.
**	The first element become the last.
*/

void	ft_stack_rotate(t_stack **head)
{
	t_stack	*tmp;
	t_stack	*current;

	if (*head && (*head)->next)
	{
		tmp = *head;
		*head = tmp->next;
		current = *head;
		while (current->next)
			current = current->next;
		current->next = tmp;
		tmp->next = NULL;
	}
}
