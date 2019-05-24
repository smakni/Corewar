/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/05/24 21:46:34 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		write_champ(t_env *env)
{
	unsigned i;
	unsigned j;
	int	id;
	unsigned char line[MAX_CHAMP_CODE_SIZE + 1];

	i = 0;
	j = 0;
	id = 0xffffffff;
	while (j < env->nb_champs)
	{
		if (!(safe_open(env->champ[j].header.prog_name, env, O_RDONLY)))
			return (FAIL);
		read(env->fd, &line, MAX_CHAMP_CODE_SIZE);
		ft_memcpy(env->champ[j].header.prog_name, &line[4], PROG_NAME_LENGTH);
		ft_memcpy(env->champ[j].header.comment,
					&line[0x8c], COMMENT_LENGTH - 10);
		env->champ[j].header.prog_size = read_multi_bytes(line, 0x8b, 2);
		if (env->champ[j].header.prog_size > CHAMP_MAX_SIZE)
		{
			ft_printf("SIZE_ERROR\n");
			return (FAIL);
		}
		ft_memcpy(&env->memory[i], &line[0x890],
					env->champ[j].header.prog_size);
		env->champ[j].player_nb = id;
		env->champ[j].r[1] = id--;
		env->champ[j].pc = i;
		env->champ[j].cycles = check_cycles(env, j);
		env->champ[j].last_live = -1; 
		if (close(env->fd) < 0)
			return (FAIL);
		i += 4096 / env->nb_champs;
		j++;
	}
	return (SUCCESS);
}
