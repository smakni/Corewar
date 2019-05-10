/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_min.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:53:28 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/15 09:53:29 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_min(t_stack *head)
{
	int		data;

	data = head->nb;
	head = head->next;
	while (head)
	{
		if (head->nb < data)
			data = head->nb;
		head = head->next;
	}
	return (data);
}
