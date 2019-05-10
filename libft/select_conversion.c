/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:41:40 by jergauth          #+#    #+#             */
/*   Updated: 2019/01/26 15:41:41 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Capital letters "DIOU" are treated as "diou" with 'l' (long) flag.
*/

void		redirection_conversion(t_flags *fl)
{
	fl->c = ft_tolower(fl->c);
	add_flag('l', fl);
}

static int	conversion_extend(t_flags *fl, t_buf *buf, va_list ap)
{
	if (fl->c == 'f')
	{
		if (!(ft_conv_double(fl, buf, ap)))
			return (0);
	}
	else if (fl->c == 'p')
	{
		if (!(ft_conv_ptr(fl, buf, ap)))
			return (0);
	}
	else
		return (0);
	return (1);
}

/*
**	Redirect the conversion to the appropriate function
*/

int			conversion(t_flags *fl, t_buf *buf, va_list ap)
{
	if (fl->c == 'C' || fl->c == 'S' || ((fl->l == 1
				&& (fl->c == 's' || fl->c == 'c'))))
		return (0);
	if (ft_strchr(INT_CONV, fl->c) || ft_strchr(UINT_CONV, fl->c))
	{
		if (!(ft_conv_numeric(fl, buf, ap)))
			return (0);
	}
	else if (ft_strchr(CHAR_CONV, fl->c))
	{
		if (!(ft_conv_str(fl, buf, ap)))
			return (0);
	}
	else
		return (conversion_extend(fl, buf, ap));
	return (1);
}
