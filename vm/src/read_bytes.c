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
	if (index < 0)
		index += MEM_SIZE;
	else if (index >= MEM_SIZE)
		index %= MEM_SIZE;
	if (n == 2)
	{
		nb = line[index % MEM_SIZE] << 8;
		nb += line[(index + 1) % MEM_SIZE];
		if (line[index] >> 7 == 1)
			nb |= (-1 & ~0xFFFF);
	}
	else if (n == 4)
	{
		nb = line[index % MEM_SIZE] << 24;
		nb += line[(index + 1) % MEM_SIZE] << 16;
		nb += line[(index + 2) % MEM_SIZE] << 8;
		nb += line[(index + 3) % MEM_SIZE];
		if (nb  >> 15 == 1)
			nb |= (-1 & ~0xFFFF);
	}
	return (nb);
}
