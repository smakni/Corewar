/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_is_nsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:19:02 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/19 16:19:02 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_is_nsort(t_stack *head, unsigned int limit, int rev)
{
	while (head && limit)
	{
		if (head->next)
		{
			if (rev == 0)
			{
				if (head->nb >= head->next->nb)
					return (0);
			}
			else
			{
				if (head->nb <= head->next->nb)
					return (0);
			}
		}
		head = head->next;
		limit--;
	}
	return (1);
}
