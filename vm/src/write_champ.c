/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/06/05 21:36:57 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	write_champ_visu(t_env *env, unsigned j)
{
	unsigned k;
	unsigned x;
	unsigned y;

	k = 0;
	wattron(env->mem, COLOR_PAIR(4 + j));
	x = k % 64 + (4096 * j / env->nb_champs % 64);
	if (x >= 64)
	{
		x -= 64;
		x *= 3;
		y = k / 64 + (4096 / env->nb_champs / 64 * j) + 1;
	}
	else
	{
		x *= 3;
		y = k / 64 + (4096 / env->nb_champs / 64 * j);
	}
	while (k < env->champ[j].header.prog_size)
	{
		mvwprintw(env->mem, y, x, "%.2x", env->memory[k]);
		x += 3;
		if (x >= 192)
		{
			x -= 192;
			y++;
		}
		k++;
	}
	wattroff(env->mem, COLOR_PAIR(4 + j));
	if (j == env->nb_champs - 1)
	{
		mvwprintw(env->infos, 0, 6, "** PAUSED ** ");
		print_infos(env);
		wrefresh(env->mem);
	}
}

int		write_champ(t_env *env)
{
	unsigned i;
	unsigned j;
	int id;
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
		env->champ[j].header.prog_size = read_bytes(line, 0x8a, 2);
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
		env->champ[j].last_live = 0;
		env->champ[j].carry = 0;
		if (close(env->fd) < 0)
			return (FAIL);
		if (env->visu == 1)
			write_champ_visu(env, j);
		i += 4096 / env->nb_champs;
		j++;
	}
	return (SUCCESS);
}
