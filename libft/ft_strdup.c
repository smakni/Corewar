/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:34:51 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/07 11:34:53 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*sdup;
	size_t	len;

	len = ft_strlen(s);
	if (!(sdup = (char*)malloc(sizeof(*sdup) * (len + 1))))
		return (0);
	while (*s)
	{
		*sdup = *s;
		s++;
		sdup++;
	}
	*sdup = '\0';
	return (sdup - len);
}
