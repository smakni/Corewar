/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_processess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:06:24 by sabri             #+#    #+#             */
/*   Updated: 2019/06/12 19:18:35 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void del_processess_visu(t_env *env)
{
	unsigned	j;
	unsigned	x;
	unsigned	y;
	int			color;

	j = 0;
	while (j < env->nb_process)
	{
		if (env->process[j].nb_live == 0)
		{
			x = env->process[j].pc % 64 * 3;
			y = env->process[j].pc / 64;
			remove_bold(env, j);
			color = mvwinch(env->mem, y, x) & A_COLOR;
			if (color == COLOR_PAIR(12))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 1, NULL);
			else if (color == COLOR_PAIR(8))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 4, NULL);
			else if (color == COLOR_PAIR(9))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 5, NULL);
			else if (color == COLOR_PAIR(10))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 6, NULL);
			else if (color == COLOR_PAIR(11))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 7, NULL);
		}
		j++;
	}
}

static void	aff_del_processess(t_env *env, unsigned j)
{
	while ((int)j >= 0)
	{
		if (env->process[j].nb_live == -1)
		{
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", j + 1,
						env->cycle_index - env->process[j].last_live - 1, env->cycle_to_die);
			env->process[j].nb_live = -2;
		}
		j--;
	}
}

int del_processess(t_env *env)
{
	unsigned	j;
	int			living_process;

	j = 0;
	living_process = 0;
	if (env->visu == 1)
		del_processess_visu(env);
	while (j < env->nb_process)
	{
		if (env->process[j].nb_live > 0)
		{
			env->process[j].nb_live = 0;
			living_process++;
		}
		else if (env->process[j].nb_live != -2)
			env->process[j].nb_live = -1;
		j++;
	}
	if (env->visu == 0)
		aff_del_processess(env, j);
	return (living_process);
}
