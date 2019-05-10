/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:39:22 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/09 12:11:10 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*trimmed;
	char const	*first;
	char const	*last;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (*s == '\0')
		return (ft_strdup(""));
	first = s;
	while (*s)
	{
		if (*s != ' ' && *s != '\n' && *s != '\t')
			last = s;
		s++;
	}
	trimmed = ft_strndup(first, (last - first) + 1);
	return (trimmed);
}
