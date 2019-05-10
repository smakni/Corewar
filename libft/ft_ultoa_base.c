/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 19:30:19 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:14 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long nb, short base)
{
	char			*str;
	int				len;
	unsigned long	n;

	if (base <= 1 || base > 16)
		return (NULL);
	len = 1;
	n = nb;
	while ((n /= base) > 0)
		len++;
	if (!(str = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = (nb % base > 9) ? (nb % base) + 55 : (nb % base) + 48;
		nb /= base;
	}
	return (str);
}
