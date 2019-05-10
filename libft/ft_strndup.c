/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:37:23 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/09 12:12:06 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*sdup;
	size_t	i;

	i = 0;
	if (!(sdup = (char*)malloc(sizeof(*sdup) * (n + 1))))
		return (NULL);
	while (s[i] && i < n)
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
