/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_rev_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:40 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:41 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Rotate all elements of the stack to the bot position.
**	The last element become the first.
*/

void	ft_stack_rev_rotate(t_stack **head)
{
	t_stack	*tmp;
	t_stack	*current;

	if (*head && (*head)->next)
	{
		tmp = *head;
		current = *head;
		while (current->next->next)
			current = current->next;
		*head = current->next;
		current->next->next = tmp;
		current->next = NULL;
	}
}
