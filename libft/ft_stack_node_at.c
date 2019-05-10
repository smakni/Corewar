/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_node_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:56 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/03 17:30:57 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return the node located at index.
*/

t_stack		*ft_stack_node_at(t_stack *head, unsigned int index)
{
	unsigned int	i;

	i = 1;
	while (head && i < index)
	{
		i++;
		head = head->next;
	}
	if (head)
		return (head);
	return (NULL);
}
