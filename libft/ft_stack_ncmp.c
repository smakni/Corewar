/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_ncmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:30:15 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/04 19:24:15 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_ncmp(t_stack *head, int data_ref, int (*f)(int, int),
				unsigned int limit)
{
	unsigned int	i;

	if (head == NULL || f == NULL)
		return (0);
	i = 0;
	while (head && i < limit)
	{
		if (f(head->nb, data_ref))
			return (1);
		head = head->next;
		i++;
	}
	return (0);
}
