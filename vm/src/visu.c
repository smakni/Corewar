/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/06 15:53:27 by sabri            ###   ########.fr       */
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
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_BLUE);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
}

void redraw_pc_2(t_env *env, int pc, int len)
{
	int x;
	int y;
	int color;

	x = pc % 64 * 3;
	y = pc / 64;
	color = mvwinch(env->mem, y, x) & A_COLOR;
	if (color == COLOR_PAIR(1))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 12, NULL);
	else if (color == COLOR_PAIR(4))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 8, NULL);
	else if (color == COLOR_PAIR(5))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 9, NULL);
	else if (color == COLOR_PAIR(6))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 10, NULL);
	else if (color == COLOR_PAIR(7))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 11, NULL);

	pc -= len;
	x = pc % 64 * 3;
	y = pc / 64;
	color = mvwinch(env->mem, y, x) & A_COLOR;
	if (color == COLOR_PAIR(12))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 1, NULL);
	else if (color == COLOR_PAIR(8))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 4, NULL);
	else if (color == COLOR_PAIR(9))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 5, NULL);
	else if (color == COLOR_PAIR(10))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 6, NULL);
	else if (color == COLOR_PAIR(11))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 7, NULL);
	//	wrefresh(env->mem);
	//	wrefresh(env->infos);
}

void redraw_pc(t_env *env, int pc, unsigned id, int len)
{
	int x;

	return (redraw_pc_2(env, pc, len));
	x = pc % 64 * 3;
	wattron(env->mem, COLOR_PAIR(UINT32_MAX - id + 8));
	mvwprintw(env->mem, pc / 64, x, "%.2x", env->memory[pc]);
	wattron(env->mem, COLOR_PAIR(UINT32_MAX - id + 8));

	wattron(env->mem, COLOR_PAIR(UINT32_MAX - id + 4));
	pc -= len;
	x = pc % 64 * 3;
	mvwprintw(env->mem, pc / 64, x, "%.2x", env->memory[pc]);
	wattroff(env->mem, COLOR_PAIR(UINT32_MAX - id + 4));
	//wrefresh(env->mem);
	//wrefresh(env->infos);
}

void update_visu(t_env *env, short dest, unsigned j)
{
	int k;
	int x;
	int y;
	int	i;

	env->champ[j].dest = dest;
	k = 0;
	i = 0;
	if (env->champ[j].id == 0xffffffff)
		i = 0;
	else if (env->champ[j].id == 0xfffffffe)
		i = 1;
	else if (env->champ[j].id == 0xfffffffd)
		i = 2;
	else if (env->champ[j].id == 0xfffffffc)
		i = 3;
	wattron(env->mem, COLOR_PAIR(4 + i));
	env->champ[j].color = 4 + i;
	x = dest % 64 * 3;
	y = dest / 64;
	env->champ[j].bold = 1;
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
	//	wrefresh(env->mem);
}

void remove_bold(t_env *env, unsigned j)
{
	int k;
	int x;
	int y;

	k = 0;
	if (env->champ[j].bold == 1)
	{
		x = env->champ[j].dest % 64 * 3;
		y = env->champ[j].dest / 64;
		k = 0;
		while (k < 4)
		{
			mvwchgat(env->mem, y, x, 2, A_NORMAL, env->champ[j].color, NULL);
			x += 3;
			if (x >= 192)
			{
				x -= 192;
				y++;
			}
			k++;
		}
		env->champ[j].bold = 0;
		env->champ[j].dest = 0;
	}
}

void print_infos(t_env *env)
{
	int i;
	unsigned j;

	i = 1;
	j = 0;
	if (env->speed == 0)
		env->speed = 50;
	wattron(env->infos, COLOR_PAIR(3));
	//	if (env->cycle_index == 0)
	mvwprintw(env->infos, i += 2, 6, "Cycles/second limit : %-10d", env->speed);
	mvwprintw(env->infos, i += 2, 6, "Cycle : %d", env->cycle_index);
	mvwprintw(env->infos, i += 2, 6, "Nb Processes : %-10d", env->nb_champs);
	i += 2;
	while (j < env->nb_player)
	{
		mvwprintw(env->infos, i, 6, "Player %d: ", j + 1);
		wattron(env->infos, COLOR_PAIR(4 + j));
		wprintw(env->infos, "%s", env->live[j].header.prog_name);
		i += 1;
		wattroff(env->infos, COLOR_PAIR(4 + j));
		mvwprintw(env->infos, i, 6, "Last live : %d", env->live[j].last_live);
		//			mvwprintw(env->infos, i, 6, "Total lives : %d", env->champ[j].nb_live);
		i += 2;
		j++;
	}
	mvwprintw(env->infos, i += 2, 6, "CYCLE_TO_DIE : %-5d", env->cycle_to_die);
	mvwprintw(env->infos, i += 2, 6, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->infos, i += 2, 6, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->infos, i += 2, 6, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(env->infos, COLOR_PAIR(3));
	wrefresh(env->infos);
	usleep(1000000 / env->speed);
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
		mvwprintw(env->infos, 0, 6, "** RUNNING **");
		wrefresh(env->infos);
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
		env->speed = 10000000;
	else if (key == 't')
		env->speed = 1;
	if (env->cycle_index > 0 && key == ' ')
	{
		mvwprintw(env->infos, 0, 6, "** PAUSED ** ");
		wrefresh(env->infos);
		while (1)
		{
			key = getch();
			if (key == ' ')
			{
				mvwprintw(env->infos, 0, 6, "** RUNNING **");
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
					env->speed = 10000000;
				else if (key == 't')
					env->speed = 1;
				print_infos(env);
			}
		}
	}
}

void first_visu(t_env *env)
{
	int i;

	i = 0;
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	env->nb_player = env->nb_champs;
	init_color_palet();
	attron(COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
	env->around_memory = subwin(stdscr, 68, 197, 0, 0);
	wborder(env->around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	env->around_infos = subwin(stdscr, 68, 58, 0, 196);
	wborder(env->around_infos, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2));
	env->mem = subwin(stdscr, 64, 193, 2, 3);
	env->infos = subwin(stdscr, 68, 58, 2, 193);
	//	update_visu(env);
	wattron(env->mem, COLOR_PAIR(1));
	while (i < 4096)
	{
		wprintw(env->mem, "%.2x", env->memory[i]);
		wprintw(env->mem, " ");
		i++;
		if (i % 64 == 0)
			wprintw(env->mem, "\n");
	}
	wattroff(env->mem, COLOR_PAIR(1));
	refresh();
	wrefresh(env->mem);
}