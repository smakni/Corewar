/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <curses.h>

void	fill_first(t_env *env)
{
	int		i;

	i = 0;
	wattron(env->mem, COLOR_PAIR(1));
	while (i < MEM_SIZE)
	{
		if (wprintw(env->mem, "%.2x ", env->memory[i]) == ERR)
			exit(-1);
		i++;
		if (i % 64 == 0 && i != MEM_SIZE)
			if (wprintw(env->mem, "\n") == ERR)
				exit(-1);
	}
	wattroff(env->mem, COLOR_PAIR(1));
}

void	update_visu(t_env *env, int dest, unsigned j)
{
	int k;
	int x;
	int y;

	env->process[j].dest = dest;
	k = 0;
	wattron(env->mem, COLOR_PAIR(env->process[j].color));
	env->process[j].bold = 1;
	wattron(env->mem, A_BOLD);
	while (k < 4)
	{
		dest %= MEM_SIZE;
		x = dest % 64 * 3;
		y = dest / 64;
		if (mvwprintw(env->mem, y, x, "%.2x", env->memory[dest++]) == ERR)
			exit_clean(env);
		k++;
	}
	wattroff(env->mem, A_BOLD);
}

void	remove_bold(t_env *env, unsigned j)
{
	int k;
	int x;
	int y;
	int dest;

	k = 0;
	if (env->process[j].bold == 1)
	{
		dest = env->process[j].dest;
		k = 0;
		while (k < 4)
		{
			x = (dest + k) % 64 * 3;
			y = (dest + k) / 64;
			mvwchgat(env->mem, y, x, 2, A_NORMAL, env->process[j].color, NULL);
			k++;
		}
		env->process[j].bold = 0;
		env->process[j].dest = 0;
	}
}
