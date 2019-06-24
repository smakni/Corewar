/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:16:27 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/24 12:16:31 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static void		handle_resize2(t_env *env, int y, int x)
{
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

static void		handle_resize(t_env *env)
{
	int x;
	int y;
	int i;

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
		handle_resize2(env, y, x);
	}
}

static void		handle_key(t_env *env, int key, char *state)
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
			mvwprintw(env->state, 0, 0, "%s", state);
			wrefresh(env->state);
		}
	}
}

static void		while_paused_events(t_env *env, int key)
{
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
			break ;
		}
		else
		{
			handle_key(env, key, "** PAUSED ** ");
			if (env->option == 1)
				print_infos(env);
		}
	}
}

void			key_events(t_env *env)
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
	handle_key(env, key, "** RUNNING **");
	if (env->cycle_index > 0 && key == ' ')
	{
		if (env->option == 1)
		{
			mvwprintw(env->state, 0, 0, "** PAUSED ** ");
			wrefresh(env->state);
		}
		while_paused_events(env, key);
	}
}
