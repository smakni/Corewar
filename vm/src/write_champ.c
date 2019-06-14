/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/06/06 15:05:42 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	write_champ_visu(t_env *env, unsigned j)
{
	unsigned	k;
	unsigned	x;
	unsigned	y;
	unsigned	start;

	k = 0;
	env->champ[j].color = 4 + j;
	wattron(env->mem, COLOR_PAIR(env->champ[j].color));
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
	start = 4096 * j  / env->nb_champs;

	wattron(env->mem, COLOR_PAIR(env->champ[j].color + 4));
	mvwprintw(env->mem, y, x, "%.2x", env->memory[start + k]);
	k++;
	x += 3;
	if (x >= 192)
	{
		x -= 192;
		y++;
	}
	wattroff(env->mem, COLOR_PAIR(env->champ[j].color + 4));
	wattron(env->mem, COLOR_PAIR(env->champ[j].color));
	while (k < env->champ[j].header.prog_size)
	{
		mvwprintw(env->mem, y, x, "%.2x", env->memory[start + k]);
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
		mvwprintw(env->infos, 0, 2, "** PAUSED ** ");
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
	if (env->visu == 1)
		first_visu(env);
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
		env->live[j].header = env->champ[j].header;
		env->live[j].last_live = 0;
		env->champ[j].id = id;
		env->champ[j].nb = j;
		env->champ[j].r[1] = id--;
		env->champ[j].pc = i;
		env->champ[j].cycles = check_cycles(env, j);
		env->champ[j].carry = 0;
		env->champ[j].live = -1;
		if (close(env->fd) < 0)
			return (FAIL);
		if (env->visu == 1)
			write_champ_visu(env, j);
		i += 4096 / env->nb_champs;
		j++;
	}
	return (SUCCESS);
}
