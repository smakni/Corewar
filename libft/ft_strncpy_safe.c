/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:56:05 by jergauth          #+#    #+#             */
/*   Updated: 2019/01/26 13:02:38 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy_safe(char *dest, const char *src, size_t n)
{
	if (n > 0)
	{
		dest = ft_strncpy(dest, src, n - 1);
		dest[n - 1] = '\0';
	}
	return (dest);
}
