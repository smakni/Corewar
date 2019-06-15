/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/14 15:11:03 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

void update_visu(t_env *env, short dest, unsigned j)
{
	int k;
	int x;
	int y;

	env->process[j].dest = dest;
	k = 0;
	wattron(env->mem, COLOR_PAIR(env->process[j].color));
	x = dest % 64 * 3;
	y = dest / 64;
	env->process[j].bold = 1;
	wattron(env->mem, A_BOLD);
	while (k < 4)
	{
		mvwprintw(env->mem, y, x, "%.2x", env->memory[dest + k]);
		x += 3;
		if (x >= 192)
		{
			x -= 192;
			y++;
		}
		k++;
	}
	wattroff(env->mem, A_BOLD);
}

void remove_bold(t_env *env, unsigned j)
{
	int k;
	int x;
	int y;

	k = 0;
	if (env->process[j].bold == 1)
	{
		x = env->process[j].dest % 64 * 3;
		y = env->process[j].dest / 64;
		k = 0;
		while (k < 4)
		{
			mvwchgat(env->mem, y, x, 2, A_NORMAL, env->process[j].color, NULL);
			x += 3;
			if (x >= 192)
			{
				x -= 192;
				y++;
			}
			k++;
		}
		env->process[j].bold = 0;
		env->process[j].dest = 0;
	}
}

void key_events(t_env *env)
{
	int key;

	key = 0;

	if (env->cycle_index > 0)
		timeout(0);
	key = getch();
	if (env->cycle_index > 0)
	{
		mvwprintw(env->infos, 0, 0, "** RUNNING **");
		wrefresh(env->infos);
	}
	if (key == 'w' && env->speed > 1 && env->speed <= 1000)
		env->speed -= 1;
	else if (key == 'e' && env->speed < 1000)
		env->speed += 1;
	else if (key == 'q' && env->speed > 10 && env->speed <= 1000)
		env->speed -= 10;
	else if (key == 'r' && env->speed < 991)
		env->speed += 10;
	else if (key == 'y')
		env->speed = -1;
	else if (key == 't')
		env->speed = 1;
	if (env->cycle_index > 0 && key == ' ')
	{
		mvwprintw(env->infos, 0, 0, "** PAUSED ** ");
		wrefresh(env->infos);
		while (1)
		{
			key = getch();
			if (key == ' ')
			{
				mvwprintw(env->infos, 0, 0, "** RUNNING **");
				wrefresh(env->infos);
				break;
			}
			else
			{
				if (key == 'w' && env->speed > 1)
					env->speed -= 1;
				else if (key == 'e' && env->speed < 1000)
					env->speed += 1;
				else if (key == 'q' && env->speed > 10)
					env->speed -= 10;
				else if (key == 'r' && env->speed < 991)
					env->speed += 10;
				else if (key == 'y')
					env->speed = -1;
				else if (key == 't')
					env->speed = 1;
				print_infos(env);
			}
		}
	}
}
