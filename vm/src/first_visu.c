/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:10:36 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/04 15:54:02 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static void		check_size(t_env *env)
{
	int	key;
	int	x;
	int	y;
	int	columns;

	columns = 254;
	if (env->option == 2)
		columns = 197;
	else if (env->option == 1 && env->verb == 1)
		columns = 311;
	getmaxyx(stdscr, y, x);
	if (y < 68 || x < columns)
	{
		while (y < 68 || x < columns)
		{
			mvprintw(y / 2, x / 2, "Terminal size too small");
			key = getch();
			if (key == KEY_RESIZE)
			{
				protect_wclear(env, stdscr);
				protect_wrefresh(env, stdscr);
			}
			getmaxyx(stdscr, y, x);
		}
	}
}

static void		first_visu_small(t_env *env)
{
	attron(COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
	if ((env->around_memory = subwin(stdscr, 68, 197, 0, 0)) == NULL)
		exit(-1);
	wborder(env->around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2));
	if ((env->mem = subwin(stdscr, 64, 193, 2, 3)) == NULL)
		exit(-1);
	fill_first(env);
	protect_wrefresh(env, stdscr);
	protect_wrefresh(env, env->mem);
}

void			create_border_windows(t_env *env)
{
	attron(COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
	if (!(env->around_memory = subwin(stdscr, 68, 197, 0, 0)))
		exit_clean(env);
	wborder(env->around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	if (!(env->around_infos = subwin(stdscr, 68, 58, 0, 196)))
		exit_clean(env);
	wborder(env->around_infos, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	if (!(env->commands = subwin(stdscr, 16, 58, 52, 196)))
		exit_clean(env);
	if (env->verb == 1)
	{
		if (!(env->around_verbos = subwin(stdscr, 68, 58, 0, 253)))
			exit_clean(env);
		wborder(env->around_verbos, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	}
	attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2));
}

void			create_inside_windows(t_env *env)
{
	if (!(env->mem = subwin(stdscr, 64, 193, 2, 3)))
		exit_clean(env);
	if (!(env->state = subwin(stdscr, 2, 52, 2, 199)))
		exit_clean(env);
	if (!(env->infos = subwin(stdscr, 51, 52, 4, 199)))
		exit_clean(env);
	if (env->verb == 1)
	{
		if (!(env->verbos = subwin(stdscr, 64, 54, 2, 255)))
			exit_clean(env);
		scrollok(env->verbos, TRUE);
	}
}

void			first_visu(t_env *env)
{
	if (initscr() == NULL)
		exit(-1);
	noecho();
	cbreak();
	curs_set(0);
	check_size(env);
	env->nb_player = env->nb_process;
	init_color_palet();
	if (env->option == 2)
		return (first_visu_small(env));
	create_border_windows(env);
	fill_commands(env);
	create_inside_windows(env);
	fill_first(env);
	protect_wrefresh(env, stdscr);
	protect_wrefresh(env, env->mem);
}
