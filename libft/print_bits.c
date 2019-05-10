/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:07:19 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/26 11:38:22 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_bits(unsigned char c)
{
	unsigned char	bits;

	bits = 128;
	while (bits > 0)
	{
		if (c & bits)
			ft_putchar('1');
		else
			ft_putchar('0');
		bits >>= 1;
	}
}
