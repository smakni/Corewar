/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:34 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:35 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_push_front(t_stack **head, t_stack *new)
{
	if (*head)
	{
		new->next = *head;
		*head = new;
	}
	else
		*head = new;
}
