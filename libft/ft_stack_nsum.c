/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_nsum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:23:54 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/04 19:23:55 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_stack_nsum(t_stack *head, unsigned int limit)
{
	long			sum;
	unsigned int	i;

	sum = 0;
	i = 0;
	while (head && i < limit)
	{
		sum += head->nb;
		head = head->next;
		i++;
	}
	return (sum);
}
