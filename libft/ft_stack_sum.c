/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_sum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:23:57 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/04 19:23:58 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_stack_sum(t_stack *head)
{
	long	sum;

	sum = 0;
	while (head)
	{
		sum += head->nb;
		head = head->next;
	}
	return (sum);
}
