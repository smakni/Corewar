/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:32:42 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/01 15:20:23 by smakni           ###   ########.fr       */
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
		if (line[index] >> 15 == 1)
			nb |= (-1 & ~0xFFFF);
	}
	return (nb);
}
