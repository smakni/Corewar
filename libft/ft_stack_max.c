/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:53:34 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/15 09:53:35 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_max(t_stack *head)
{
	int		data;

	data = head->nb;
	head = head->next;
	while (head)
	{
		if (head->nb > data)
			data = head->nb;
		head = head->next;
	}
	return (data);
}
