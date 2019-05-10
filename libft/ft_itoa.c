/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:19:46 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/08 11:49:43 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_getlen(int nb, int *isneg)
{
	unsigned int	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		*isneg = 1;
	}
	else
		*isneg = 0;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char				*ft_itoa(int n)
{
	unsigned int	len;
	int				isneg;
	char			*str;

	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (n == 0)
		return (str = ft_strdup("0"));
	len = ft_getlen(n, &isneg);
	if (!(str = (char*)malloc(sizeof(*str) * (len + isneg + 1))))
		return (NULL);
	if (isneg)
	{
		*str++ = '-';
		n = -n;
	}
	while (n)
	{
		*str++ = (n % 10) + 48;
		n /= 10;
	}
	*str = '\0';
	str -= len;
	ft_strrev(str);
	return (str - isneg);
}
