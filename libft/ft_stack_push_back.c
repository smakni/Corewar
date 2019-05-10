/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:44:04 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 14:44:06 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_push_back(t_stack **head, t_stack *new)
{
	t_stack	*current;

	if (head == NULL || *head == NULL)
		(*head) = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
