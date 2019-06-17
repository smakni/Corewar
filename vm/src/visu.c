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

static void mv_back(t_env *env)
{
	int key;
	int where;
	int cycle;

	mvwprintw(env->state, 0, 0, "EXPLORATION MODE");
	wrefresh(env->state);
	fill_commands_mv_back(env);
	where = env->cycle_index % 1000;
	cycle = env->cycle_index;
	while (1)
	{
		key = getch();
		if (key == 'p')
		{
			fill_commands(env);
			overwrite(env->trace[env->cycle_index % 1000], env->mem);
			overwrite(env->traceinfos[env->cycle_index % 1000], env->infos);
			wrefresh(env->mem);
			wrefresh(env->infos);
			break;
		}
		else if (key == 'h' && cycle > env->cycle_index - 990 && cycle > 9)
		{
			where -= 10;
			cycle -= 10;
			if (where < 0)
				where += 1000;
			overwrite(env->trace[where], env->mem);
			overwrite(env->traceinfos[where], env->infos);
			wrefresh(env->mem);
			wrefresh(env->infos);
		}
		else if (key == 'j' && cycle > env->cycle_index - 1000 && cycle > 0)
		{
			where -= 1;
			cycle -= 1;
			if (where < 0)
				where += 1000;
			overwrite(env->trace[where], env->mem);
			overwrite(env->traceinfos[where], env->infos);
			wrefresh(env->mem);
			wrefresh(env->infos);
		}
		else if (key == 'k' && cycle < env->cycle_index)
		{
			where += 1;
			cycle += 1;
			if (where >= 1000)
				where -= 1000;
			overwrite(env->trace[where], env->mem);
			overwrite(env->traceinfos[where], env->infos);
			wrefresh(env->mem);
			wrefresh(env->infos);
		}
		else if (key == 'l' && cycle < env->cycle_index - 9)
		{
			where += 10;
			cycle += 10;
			if (where >= 1000)
				where -= 1000;
			overwrite(env->trace[where], env->mem);
			overwrite(env->traceinfos[where], env->infos);
			wrefresh(env->mem);
			wrefresh(env->infos);
		}
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
		mvwprintw(env->state, 0, 0, "** RUNNING **");
		wrefresh(env->state);
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
	else if (env->mvintime == 1 && key == 'p')
	{
		mv_back(env);
		werase(env->state);
		mvwprintw(env->state, 0, 0, "** RUNNING **");
		wrefresh(env->state);
	}
	if (env->cycle_index > 0 && key == ' ')
	{
		mvwprintw(env->state, 0, 0, "** PAUSED ** ");
		wrefresh(env->state);
		while (1)
		{
			key = getch();
			if (key == ' ')
			{
				mvwprintw(env->state, 0, 0, "** RUNNING **");
				wrefresh(env->state);
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
				else if (env->mvintime == 1 && key == 'p')
				{
					mv_back(env);
					werase(env->state);
					mvwprintw(env->state, 0, 0, "** PAUSED ** ");
					wrefresh(env->state);
				}
				print_infos(env);
			}
		}
	}
}
