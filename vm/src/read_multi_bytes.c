/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_multi_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:53:38 by smakni            #+#    #+#             */
/*   Updated: 2019/05/17 17:16:13 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		read_multi_bytes(unsigned char *line, int index, int nb_bytes)
{
	int multi_byte;

	multi_byte = 0;
	if (nb_bytes == 2)
	{
		multi_byte = line[index];
		multi_byte += line[index - 1] << 8;
	}
	if (nb_bytes == 4)
	{
		multi_byte = line[index];
		multi_byte += line[index - 1] << 8;
		multi_byte += line[index - 2] << 16;
		multi_byte += line[index - 3] << 24;
	}
	return (multi_byte);
}