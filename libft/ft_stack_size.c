/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:53:43 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/15 09:53:44 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_stack_size(t_stack *head)
{
	unsigned int	size;

	size = 0;
	if (head != NULL)
	{
		while (head)
		{
			head = head->next;
			size++;
		}
	}
	return (size);
}
