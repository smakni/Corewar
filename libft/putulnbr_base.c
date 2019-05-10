/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putulnbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:24:41 by jergauth          #+#    #+#             */
/*   Updated: 2018/12/28 19:24:29 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putulnbr_base(unsigned long n, unsigned int base)
{
	if (base > 1 && base <= 16)
	{
		if (n >= base)
			putulnbr_base(n / base, base);
		(n % base) > 9 ? ft_putchar(n % base + 55) : ft_putchar(n % base + 48);
	}
}
