/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/05/21 17:15:51 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	write_champ(t_env *env)
{
	int i;
	int j;
	int fd;
	int	id;
	unsigned char line[MAX_CHAMP_CODE_SIZE + 1];

	i = 0;
	j = 0;
	id = 0xffffffff;
	while (j < env->nb_champs)
	{
		fd = open(env->champ[j].header.prog_name, O_RDONLY);
		read(fd, &line, MAX_CHAMP_CODE_SIZE);
		ft_memcpy(env->champ[j].header.prog_name, &line[4], PROG_NAME_LENGTH);
		ft_memcpy(env->champ[j].header.comment,
					&line[0x8c], COMMENT_LENGTH - 10);
		env->champ[j].header.prog_size = read_multi_bytes(line, 0x8b, 2);
		if (env->champ[j].header.prog_size > CHAMP_MAX_SIZE)
		{
			ft_printf("SIZE_ERROR\n");
			exit (0);
		}
		ft_memcpy(&env->memory[i], &line[0x890],
					env->champ[j].header.prog_size);
		env->champ[j].player_nb = id;
		env->champ[j].r[1] = id--;
		env->champ[j].pc = i;
		env->champ[j].cycles = check_cycles(env, j);
		close(fd);
		i += 4096 / env->nb_champs;
		j++;
	}
}
