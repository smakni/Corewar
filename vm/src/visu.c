/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/24 12:20:03 by vrenaudi         ###   ########.fr       */
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
	wattron(env->mem, COLOR_PAIR(env->process[j].color));
	env->process[j].bold = 1;
	wattron(env->mem, A_BOLD);
	while (k < 4)
	{
		x = dest % 64 * 3;
		y = dest / 64;
		mvwprintw(env->mem, y, x, "%.2x", env->memory[dest++]);
		if (dest >= 4096)
			dest -= 4096;
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
			x = dest % 64 * 3;
			y = dest / 64;
			mvwchgat(env->mem, y, x, 2, A_NORMAL, env->process[j].color, NULL);
			dest++;
			if (dest >= 4096)
				dest -= 4096;
			k++;
		}
		env->process[j].bold = 0;
		env->process[j].dest = 0;
	}
}
