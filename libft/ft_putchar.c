/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:30:45 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/12 12:32:09 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	char	l;

	if (!(c & 0x80))
		write(1, &c, 1);
	else
	{
		l = ((unsigned char)c <= 191 ? 0xC2 : 0xC3);
		l = (char)(0xC2 | ((unsigned char)l));
		write(1, &l, 1);
		l = (char)(0xBF & c);
		write(1, &l, 1);
	}
}
