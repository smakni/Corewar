/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:31:48 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/22 13:31:49 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stack_cmp(t_stack *head, int data_ref, int (*f)(int, int))
{
	if (head == NULL || f == NULL)
		return (0);
	while (head)
	{
		if (f(head->nb, data_ref))
			return (1);
		head = head->next;
	}
	return (0);
}
