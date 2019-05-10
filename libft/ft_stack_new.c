/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:05:20 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/13 11:05:21 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stack_new(int nb)
{
	t_stack	*new;

	if (!(new = (t_stack*)malloc(sizeof(*new))))
		return (NULL);
	new->nb = nb;
	new->next = NULL;
	return (new);
}
