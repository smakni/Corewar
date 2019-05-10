/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:53:16 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/15 09:53:17 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return the nb of the element at index.
*/

int		ft_stack_at(t_stack *head, unsigned int index)
{
	unsigned int	i;

	i = 1;
	while (head && i <= index)
	{
		i++;
		head = head->next;
	}
	if (head)
		return (head->nb);
	return (0);
}
