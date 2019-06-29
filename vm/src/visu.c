/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/29 12:25:36 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

void	update_visu(t_env *env, int dest, unsigned j)
{
	int k;
	int x;
	int y;

	env->process[j].dest = dest;
	k = 0;
	if (wattron(env->mem, COLOR_PAIR(env->process[j].color)) == ERR)
		exit_clean(env);
	env->process[j].bold = 1;
	if (wattron(env->mem, A_BOLD) == ERR)
		exit_clean(env);
	while (k < 4)
	{
		x = dest % 64 * 3;
		y = dest / 64;
		if (mvwprintw(env->mem, y, x, "%.2x", env->memory[dest++]) == ERR)
			exit_clean(env);
		if (dest >= MEM_SIZE)
			dest -= MEM_SIZE;
		k++;
	}
	if (wattroff(env->mem, A_BOLD) == ERR)
		exit_clean(env);
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
			x = dest % 64 * 3;
			y = dest / 64;
			protect_mvwchgat(env, y, x, env->process[j].color);
			dest++;
			if (dest >= MEM_SIZE)
				dest -= MEM_SIZE;
			k++;
		}
		env->process[j].bold = 0;
		env->process[j].dest = 0;
	}
}
