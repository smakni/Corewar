/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/05/17 15:54:27 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	write_champ(t_env *env)
{
	int i;
	int j;
	int fd;
	int tmp;
	unsigned char line[MAX_CHAMP_CODE_SIZE];

	i = 0;
	j = 0;
	tmp = 0;
	while (j < env->nb_champs)
	{
		fd = open(env->champ[j].name, O_RDONLY);
		read(fd, &line, MAX_CHAMP_CODE_SIZE);
		tmp = line[0x8b];
		tmp += line[0x8a] << 8;
		if (tmp > CHAMP_MAX_SIZE)
		{
			ft_printf("SIZE_ERROR\n");
			exit (0);
		}
		ft_memcpy(&env->memory[i], &line[0x890], tmp);
		close(fd);
		i += 4096 / env->nb_champs;
		j++;
	}
}