/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:30 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:31 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_print(t_stack *current)
{
	if (current != NULL)
	{
		while (current)
		{
			ft_putnbr(current->nb);
			ft_putchar('\n');
			current = current->next;
		}
	}
}
