/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:15:06 by jergauth          #+#    #+#             */
/*   Updated: 2018/12/26 19:17:11 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putunbr_base(unsigned int n, unsigned int base)
{
	if (base > 1 && base <= 16)
	{
		if (n >= base)
			putnbr_base(n / base, base);
		(n % base) > 9 ? ft_putchar(n % base + 55) : ft_putchar(n % base + 48);
	}
}
