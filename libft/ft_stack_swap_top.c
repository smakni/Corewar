/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_swap_top.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:53 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:54 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Swap the two first elem of the stack.
*/

void	ft_stack_swap_top(t_stack **head)
{
	t_stack	*new_head;
	t_stack	*new_second;

	if (*head && (*head)->next)
	{
		new_head = (*head)->next;
		new_second = *head;
		new_second->next = new_head->next;
		new_head->next = new_second;
		*head = new_head;
	}
}
