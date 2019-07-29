/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:39:52 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		check_last(t_env *env, unsigned j)
{
	if (j == env->nb_process - 1)
	{
		if (env->option == 1)
		{
			mvwprintw(env->state, 0, 0, "** PAUSED ** ");
			print_infos(env);
			protect_wrefresh(env, env->state);
			env->traceinfos[env->cycle_index] = protect_dupwin(env, env->infos);
		}
		protect_wrefresh(env, env->mem);
		if (!(env->trace[env->cycle_index] = dupwin(env->mem)))
			exit_clean(env);
	}
}

static void		write_champ_body(t_env *env, unsigned y, unsigned x, unsigned j)
{
	unsigned	k;
	unsigned	start;

	k = 1;
	start = MEM_SIZE * j / env->nb_process;
	wattron(env->mem, COLOR_PAIR(env->process[j].color));
	while (k < env->player[j].header.prog_size)
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
}

void			write_champ_visu(t_env *env, unsigned j)
{
	unsigned	x;
	unsigned	y;

	env->process[j].color = 4 + j;
	x = MEM_SIZE * j / env->nb_process % 64 * 3;
	y = MEM_SIZE / env->nb_process / 64 * j;
	wattron(env->mem, COLOR_PAIR(env->process[j].color + 4));
	mvwprintw(env->mem, y, x, "%.2x",
				env->memory[MEM_SIZE * j / env->nb_process]);
	x += 3;
	if (x >= 192)
	{
		x -= 192;
		y++;
	}
	wattroff(env->mem, COLOR_PAIR(env->process[j].color + 4));
	write_champ_body(env, y, x, j);
	check_last(env, j);
}
