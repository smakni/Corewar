/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putllnbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:27:49 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:28 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putllnbr_base(long long n, short base)
{
	if (base > 1 && base <= 16)
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = -n;
		}
		if (n >= base)
			putllnbr_base(n / base, base);
		(n % base) > 9 ? ft_putchar(n % base + 55) : ft_putchar(n % base + 48);
	}
}
