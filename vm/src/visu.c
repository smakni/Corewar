/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/24 11:56:46 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

void update_visu(t_env *env, int dest, unsigned j)
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
		mvwprintw(env->mem, y, x, "%.2x", env->memory[dest++]);
		if (dest >= 4096)
		{
			dest -= 4096;
			x = dest % 64 * 3;
			y = dest / 64;
		}
		else
		{
			x += 3;
			if (x >= 192)
			{
				x -= 192;
				y++;
			}
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
	int dest;

	k = 0;
	if (env->process[j].bold == 1)
	{
		dest = env->process[j].dest;
		x = env->process[j].dest % 64 * 3;
		y = env->process[j].dest / 64;
		k = 0;
		while (k < 4)
		{
			mvwchgat(env->mem, y, x, 2, A_NORMAL, env->process[j].color, NULL);
			if (++dest >= 4096)
			{
				dest -= 4096;
				x = dest % 64 * 3;
				y = dest / 64;
			}
			else
			{
				x += 3;
				if (x >= 192)
				{
					x -= 192;
					y++;
				}
			}
			k++;
		}
		env->process[j].bold = 0;
		env->process[j].dest = 0;
	}
}

static void handle_resize(t_env *env)
{
	int	x;
	int	y;
	int	i;
	
	getmaxyx(stdscr, y, x);
	if (y < 68 || x < 255)
	{
		timeout(-1);
		i = 0;
		while (i < GO_BACK && i < env->cycle_index)
		{
			delwin(env->trace[i]);
			if (env->option == 1)
				delwin(env->traceinfos[i]);
			i++;
		}
		delwin(env->mem);
		delwin(env->around_memory);
		if (env->option == 1)
		{
			delwin(env->state);
			delwin(env->commands);
			delwin(env->infos);
			delwin(env->around_infos);
		}
		clear();
		mvprintw(y / 2, x / 2, "Terminal size too small");
		mvprintw(y / 2 + 1, x / 2, "Quitting");
		timeout(-1);
		while (1)
			if (getch())
			{
				endwin();
            	exit(-1);
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
	if (env->cycle_index > 0 && env->option == 1)
	{
		mvwprintw(env->state, 0, 0, "** RUNNING **");
		wrefresh(env->state);
	}
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
	else if (key == KEY_RESIZE)
		handle_resize(env);
	else if (env->goback == 1 && key == 'p')
	{
		mv_back(env);
		if (env->option == 1)
		{
			werase(env->state);
			mvwprintw(env->state, 0, 0, "** RUNNING **");
			wrefresh(env->state);
		}
	}
	if (env->cycle_index > 0 && key == ' ')
	{
		if (env->option == 1)
		{
			mvwprintw(env->state, 0, 0, "** PAUSED ** ");
			wrefresh(env->state);
		}
		while (1)
		{
			key = getch();
			if (key == ' ')
			{
				if (env->option == 1)
				{
					mvwprintw(env->state, 0, 0, "** RUNNING **");
					wrefresh(env->state);
				}
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
				else if (key == KEY_RESIZE)
					handle_resize(env);
				else if (env->goback == 1 && key == 'p')
				{
					mv_back(env);
					if (env->option == 1)
					{
						werase(env->state);
						mvwprintw(env->state, 0, 0, "** PAUSED **");
						wrefresh(env->state);
					}
				}
				if (env->option == 1)
					print_infos(env);
			}
		}
	}
}
