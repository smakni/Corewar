/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_multi_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:53:38 by smakni            #+#    #+#             */
/*   Updated: 2019/05/31 17:27:14 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		read_multi_bytes(unsigned char *line, int index, int nb_bytes)
{
	int multi_byte;

	multi_byte = 0;
	if (nb_bytes == 2)
	{
		multi_byte = line[index % MEM_SIZE];
		multi_byte += line[index - 1 % MEM_SIZE] << 8;
	}
	if (nb_bytes == 4)
	{
		multi_byte = line[index % MEM_SIZE];
		multi_byte += line[index - 1 % MEM_SIZE] << 8;
		multi_byte += line[index - 2 % MEM_SIZE] << 16;
		multi_byte += line[index - 3 % MEM_SIZE] << 24;
	}
	return (multi_byte);
}

int	read_bytes(t_env *env, int index)
{
	int	ret;

	ret = 0;
	ret += env->memory[index] << 24;
	ret += env->memory[index + 1] << 16;
	ret += env->memory[index + 2] << 8;
	ret += env->memory[index + 3];
	return (ret);
}
