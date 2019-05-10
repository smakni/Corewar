/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:21:41 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/07 11:29:10 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*block;

	if (!(block = (void*)malloc(sizeof(*block) * size)))
		return (NULL);
	ft_bzero(block, size);
	return (block);
}
