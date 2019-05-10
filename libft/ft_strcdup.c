/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:41:26 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/19 13:41:29 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *str, const char limit)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (str == NULL)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != limit)
		len++;
	if (!(dup = (char*)malloc(sizeof(*dup) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
