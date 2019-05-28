/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/27 11:30:38 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static void init_color_palet(void)
{
	start_color();
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
}

static void print_infos(t_env *env)
{
	int i;
	unsigned j;

	i = 3;
	j = 0;
	wattron(env->infos, COLOR_PAIR(3));
//	if (env->cycle_index == 0)
		while (j < env->save_nb_champs)
		{
			mvwprintw(env->infos, i, 6, "Player %d: ", j + 1);
			wattron(env->infos, COLOR_PAIR(4 + j));
			wprintw(env->infos, "%s", env->champ[j].header.prog_name);
			i += 1;
			wattroff(env->infos, COLOR_PAIR(4 + j));
			mvwprintw(env->infos, i, 6, "Last live : %d", env->champ[j].last_live);
			i += 1;
			mvwprintw(env->infos, i, 6, "Total lives : %d", env->champ[j].nb_live);
			i += 2;
			j++;
		}
//	else
//		i += 2 * env->save_nb_champs;
	mvwprintw(env->infos, i += 2, 6, "Cycle : %d", env->cycle_index);
	mvwprintw(env->infos, i += 2, 6, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvwprintw(env->infos, i += 2, 6, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->infos, i += 2, 6, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->infos, i += 2, 6, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(env->infos, COLOR_PAIR(3));
	wrefresh(env->infos);
}

void first_visu(t_env *env)
{
	initscr();
	noecho();
	cbreak();
	env->save_nb_champs = env->nb_champs;
	while (1)
	{
		init_color_palet();
		attron(COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
		env->around_memory = subwin(stdscr, 68, 197, 0, 0);
		wborder(env->around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		env->around_infos = subwin(stdscr, 68, 58, 0, 196);
		wborder(env->around_infos, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2));
		env->mem = subwin(stdscr, 64, 193, 2, 3);
		env->infos = subwin(stdscr, 68, 58, 2, 193);
		update_visu(env);
		refresh();
		if (getch())
			break;
	}
}

void update_visu(t_env *env)
{
	int i;
	unsigned j;

	i = 0;
	if (env->cycle_index == 1)
		timeout(0);
	if (env->cycle_index > 0 && getch() == ' ')
	{
		while (1)
			if (getch() == ' ')
				break;
	}
	wattron(env->mem, COLOR_PAIR(1));
	while (i < 4096)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			if (env->champ[j].pc == (unsigned)i)
			{
				if (env->champ[j].player_nb == 0xffffffff)
					wattron(env->mem, COLOR_PAIR(4));
				else if (env->champ[j].player_nb == 0xfffffffe)
					wattron(env->mem, COLOR_PAIR(5));
				else if (env->champ[j].player_nb == 0xfffffffd)
					wattron(env->mem, COLOR_PAIR(6));
				else if (env->champ[j].player_nb == 0xfffffffc)
					wattron(env->mem, COLOR_PAIR(7));
			}
			j++;
		}
		wprintw(env->mem, "%.2x", env->memory[i]);
		wprintw(env->mem, " ");
		wattron(env->mem, COLOR_PAIR(1));
		i++;
		if (i % 64 == 0)
			wprintw(env->mem, "\n");
	}
	wmove(env->mem, 0, 0);
	wrefresh(env->mem);
	wattroff(env->mem, COLOR_PAIR(1));
	print_infos(env);
}