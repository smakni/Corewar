/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_nmin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 20:18:45 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/22 20:18:46 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_nmin(t_stack *head, unsigned int limit)
{
	int				data;
	unsigned int	i;

	data = head->nb;
	head = head->next;
	i = 1;
	while (head && i < limit)
	{
		if (head->nb < data)
			data = head->nb;
		head = head->next;
		i++;
	}
	return (data);
}
