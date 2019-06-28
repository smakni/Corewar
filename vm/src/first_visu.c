/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:10:36 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/17 18:56:03 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

void			protect_wclear(t_env *env, WINDOW *toclear)
{
	if (wclear(toclear) == ERR)
		exit_clean(env);
}

void			protect_werase(t_env *env, WINDOW *toerase)
{
	if (werase(toerase) == ERR)
		exit_clean(env);
}

void			protect_wrefresh(t_env *env, WINDOW *torefresh)
{
	if (wrefresh(torefresh) == ERR)
		exit_clean(env);
}

void			exit_clean(t_env *env)
{
	delwin(env->infos);
	delwin(env->around_infos);
	delwin(env->mem);
	delwin(env->around_memory);
	delwin(env->state);
	delwin(env->commands);
	delwin(env->verbos);
	delwin(env->around_verbos);
	curs_set(1);
	endwin();
	exit(-1);
}

static void		init_color_palet(void)
{
	if (start_color() == ERR)
		exit(-1);
	init_color(COLOR_CYAN, 460, 460, 460);
	init_color(COLOR_MAGENTA, 520, 520, 520);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_BLUE);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
	init_pair(13, COLOR_WHITE, COLOR_GREEN);
	init_pair(14, COLOR_WHITE, COLOR_BLUE);
	init_pair(15, COLOR_WHITE, COLOR_RED);
	init_pair(16, COLOR_WHITE, COLOR_YELLOW);
}

static void		fill_first(t_env *env)
{
	int		i;

	i = 0;
	if (wattron(env->mem, COLOR_PAIR(1)) == ERR)
		exit(-1);
	while (i < 4096)
	{
		if (wprintw(env->mem, "%.2x ", env->memory[i]) == ERR)
			exit(-1);
		i++;
		if (i % 64 == 0 && i != 4096)
			if (wprintw(env->mem, "\n") == ERR)
				exit(-1);
	}
	if (wattroff(env->mem, COLOR_PAIR(1)) == ERR)
		exit(-1);
}

static void		check_size(t_env *env)
{
	int	key;
	int	x;
	int	y;

	if (getmaxyx(stdscr, y, x) == ERR)
		exit(-1);
	if (y < 68 || x < 255)
	{
		while (1)
		{
			if (mvprintw(y / 2, x / 2, "Terminal size too small") == ERR)
				exit(-1);
			if ((key = getch()) == ERR)
				exit(-1);
			if (key == KEY_RESIZE)
			{
				protect_wclear(env, stdscr);
				protect_wrefresh(env, stdscr);
			}
			if (getmaxyx(stdscr, y, x) == ERR)
				exit(-1);
			if (y >= 68 && x >= 255)
				break ;
		}
	}
}

static void		first_visu_small(t_env *env)
{
	if (attron(COLOR_PAIR(2) | A_REVERSE | A_STANDOUT) == ERR)
		exit(-1);
	if ((env->around_memory = subwin(stdscr, 68, 197, 0, 0)) == NULL)
		exit(-1);
	if ((wborder(env->around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ')) == ERR)
		exit(-1);
	if ((attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2))) == ERR)
		exit(-1);
	if ((env->mem = subwin(stdscr, 64, 193, 2, 3)) == NULL)
		exit(-1);
	fill_first(env);
	protect_wrefresh(env, stdscr);
	protect_wrefresh(env, env->mem);
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
	fill_commands(env);
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
	fill_first(env);
	protect_wrefresh(env, stdscr);
	protect_wrefresh(env, env->mem);
}
