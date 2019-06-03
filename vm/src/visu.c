/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/30 20:35:21 by jergauth         ###   ########.fr       */
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
}

void redraw_pc(t_env *env, int pc, unsigned player_nb, int len)
{
	int x;

	x = pc % 64 * 3;
	mvwprintw(env->infos, 40, 6, "Pc %d: ", pc);
	mvwprintw(env->infos, 42, 6, "Player_nb : %u", player_nb);
	mvwprintw(env->infos, 44, 6, "len %d: ", len);
	mvwprintw(env->infos, 46, 6, "x %d: ", pc % 64 * 3);

	wattron(env->mem, COLOR_PAIR(UINT32_MAX - player_nb + 8));
	mvwprintw(env->mem, pc / 64, x, "%.2x", env->memory[pc]);
	wattron(env->mem, COLOR_PAIR(UINT32_MAX - player_nb + 8));

	wattron(env->mem, COLOR_PAIR(UINT32_MAX - player_nb + 4));
	pc -= len;
	x = pc % 64 * 3;
	mvwprintw(env->mem, pc / 64, x, "%.2x", env->memory[pc]);
	wattroff(env->mem, COLOR_PAIR(UINT32_MAX - player_nb + 4));
	wrefresh(env->mem);
	//read(0,0,1);
}

void	update_visu(t_env *env, short dest, unsigned j)
{
	int k;
	int			x;
	int			y;

	k = 0;
	mvwprintw(env->infos, 1, 6, "dest:%d", dest);
	if (env->champ[j].player_nb == 0xffffffff)
		j = 0;
	else if (env->champ[j].player_nb == 0xfffffffe)
		j = 1;
	else if (env->champ[j].player_nb == 0xfffffffd)
		j = 2;
	else if (env->champ[j].player_nb == 0xfffffffc)
		j = 3;
	wattron(env->mem, COLOR_PAIR(4 + j));
	x = dest % 64 * 3;
	y = dest / 64;
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
	wrefresh(env->mem);
}

void print_infos(t_env *env)
{
	int i;
	unsigned j;

	i = 3;
	j = 0;
	if (env->speed == 0)
		env->speed = 50;
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
		//		i += 1;
		//			mvwprintw(env->infos, i, 6, "Total lives : %d", env->champ[j].nb_live);
		i += 2;
		j++;
	}
	//	else
	//		i += 2 * env->save_nb_champs;
	mvwprintw(env->infos, i += 2, 6, "Cycle : %d", env->cycle_index);
	mvwprintw(env->infos, i += 2, 6, "Nb Processes : %d", env->nb_champs);
	mvwprintw(env->infos, i += 2, 6, "CYCLE_TO_DIE : %d", env->cycle_to_die);
	mvwprintw(env->infos, i += 2, 6, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->infos, i += 2, 6, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->infos, i += 2, 6, "MAX_CHECKS : %d", MAX_CHECKS);
	mvwprintw(env->infos, i += 2, 6, "speed : %- 5d", env->speed);
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
	if (key == 'w' && env->speed > 1)
		env->speed -= 1;
	if (key == 'e' && env->speed < 1000)
		env->speed += 1;
	if (key == 'q' && env->speed > 10)
		env->speed -= 10;
	if (key == 'r' && env->speed < 991)
		env->speed += 10;
	if (env->cycle_index > 0 && key == ' ')
	{
		while (1)
		{
			key = getch();
			if (key == ' ')
				break;
			if (key == 'w' && env->speed > 10)
			{
				env->speed -= 10;
				print_infos(env);
			}
			if (key == 'e' && env->speed < 1000)
			{
				env->speed += 10;
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
	env->save_nb_champs = env->nb_champs;
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