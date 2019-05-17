/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/05/17 17:17:43 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	write_champ(t_env *env)
{
	int i;
	int j;
	int fd;
	int champ_size;
	unsigned char line[MAX_CHAMP_CODE_SIZE];

	i = 0;
	j = 0;
	champ_size = 0;
	while (j < env->nb_champs)
	{
		fd = open(env->champ[j].name, O_RDONLY);
		read(fd, &line, MAX_CHAMP_CODE_SIZE);
		champ_size = read_multi_bytes(line, 0x8b, 2);
		if (champ_size > CHAMP_MAX_SIZE)
		{
			ft_printf("SIZE_ERROR\n");
			exit (0);
		}
		ft_memcpy(&env->memory[i], &line[0x890], champ_size);
		close(fd);
		i += 4096 / env->nb_champs;
		j++;
	}
}