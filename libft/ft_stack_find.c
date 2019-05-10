/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:53:24 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/15 09:53:25 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return the index of the first element which the nb is equal to the
**	nb_ref.
*/

unsigned int		ft_stack_find(t_stack *head, int nb_ref)
{
	unsigned int	i;

	if (head == NULL)
		return (0);
	i = 1;
	while (head)
	{
		if (head->nb == nb_ref)
			return (i);
		i++;
		head = head->next;
	}
	return (0);
}
