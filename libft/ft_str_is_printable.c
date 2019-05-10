/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:32:07 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/07 11:32:09 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_printable(const char *str)
{
	while (*str)
	{
		if (!ft_isprint(*str))
			return (0);
		str++;
	}
	return (1);
}
