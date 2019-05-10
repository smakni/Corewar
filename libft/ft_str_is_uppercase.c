/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:32:14 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/07 11:32:15 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_uppercase(const char *str)
{
	while (*str)
	{
		if (!ft_isupper(*str))
			return (0);
		str++;
	}
	return (1);
}
