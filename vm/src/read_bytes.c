/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:53:38 by smakni            #+#    #+#             */
/*   Updated: 2019/05/31 17:27:14 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		read_bytes(unsigned char *line, int index, int n)
{
	int nb;

	nb = 0;
	if (n == 2)
	{
		nb = line[index] << 8;
		nb += line[index + 1];
		if (line[index] >> 7 == 1)
			nb = (char)nb;
	}
	else if (n == 4)
	{
		nb = line[index] << 24;
		nb += line[index + 1] << 16;
		nb += line[index + 2] << 8;
		nb += line[index + 3];
		if (nb  >> 15 == 1)
			nb = (char)nb;
	}
	return (nb);
}
