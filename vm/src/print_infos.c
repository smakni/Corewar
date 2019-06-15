/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:10:51 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/14 15:10:52 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static int	count_live(t_env *env, unsigned j)
{
	int			nb_live;
	unsigned	i;

	nb_live = 0;
	i = 0;
	while (i < env->nb_proc)
	{
		if (env->proc[i].id == UINT32_MAX - j && env->proc[i].nb_live >= 0)
			nb_live += env->proc[i].nb_live;
//		if (env->proc[i].id == UINT32_MAX - j && env->proc[i].nb_live > -1)
		//	(*nb_process)++;
		i++;
	}
	return (nb_live);
}

void print_infos(t_env *env)
{
	int i;
	int	nb_live;
//	int	nb_process;
	unsigned j;

	i = 0;
	j = 0;
	if (env->speed == 0)
		env->speed = 50;
	wattron(env->infos, COLOR_PAIR(3));
	mvwprintw(env->infos, i += 2, 0, "Cycles/second limit : %-10d", env->speed);
	mvwprintw(env->infos, i += 2, 0, "Cycle : %d", env->cycle_index);
	mvwprintw(env->infos, i += 2, 0, "Nb Processes : %-10d", env->nb_proc);
	i += 2;
	while (j < env->nb_player)
	{
	//	nb_process = 0;
		mvwprintw(env->infos, i, 0, "Player %d: ", j + 1);
		wattron(env->infos, COLOR_PAIR(4 + j));
		wprintw(env->infos, "%s", env->player[j].header.prog_name);
		i++;
		wattroff(env->infos, COLOR_PAIR(4 + j));
		mvwprintw(env->infos, i++, 2, "Last live : %d", env->player[j].last_live);
		nb_live = count_live(env, j);
		mvwprintw(env->infos, i, 2, "Total lives during current cycle : %-10d", nb_live);
		i += 2;
		j++;
	}
	mvwprintw(env->infos, i, 0, "CYCLE_TO_DIE : %-5d", env->cycle_to_die);
    if (env->cycle_index < 1)
    {
        mvwprintw(env->infos, i += 2, 0, "CYCLE_DELTA : %d", CYCLE_DELTA);
        mvwprintw(env->infos, i += 2, 0, "NBR_LIVE : %d", NBR_LIVE);
        mvwprintw(env->infos, i += 2, 0, "MAX_CHECKS : %d", MAX_CHECKS);
    }
	wattroff(env->infos, COLOR_PAIR(3));
	wrefresh(env->infos);
	if (env->speed != -1)
		usleep(1000000 / env->speed);
}