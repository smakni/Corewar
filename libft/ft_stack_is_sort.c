/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_is_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 11:13:12 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/16 11:13:13 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_is_sort(t_stack *head, int rev)
{
	while (head)
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
	}
	return (1);
}
