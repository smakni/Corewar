/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:43:03 by jergauth          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:00 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long nb, short base)
{
	char				*str;
	int					len;
	unsigned long long	n;

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
