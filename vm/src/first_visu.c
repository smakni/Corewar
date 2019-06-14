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
	init_pair(13, COLOR_WHITE, COLOR_GREEN);
	init_pair(14, COLOR_WHITE, COLOR_BLUE);
	init_pair(15, COLOR_WHITE, COLOR_RED);
	init_pair(16, COLOR_WHITE, COLOR_YELLOW);
}

static void	fill_commands(t_env *env)
{
	wattrset(env->commands, A_NORMAL | COLOR_PAIR(3));
	mvwprintw(env->commands, 1, 2, "COMMANDS :");
	mvwprintw(env->commands, 3, 2, "Press any key to launch");
	mvwprintw(env->commands, 5, 2, "Speed :");
	mvwprintw(env->commands, 6, 4, "-10 cycles/second : q");
	mvwprintw(env->commands, 7, 4, "-1 cycle/second : w");
	mvwprintw(env->commands, 8, 4, "+1 cycle/second : e");
	mvwprintw(env->commands, 9, 4, "+10 cycle/second : r");
	mvwprintw(env->commands, 10, 4, "cycle/second = 1 : t");
	mvwprintw(env->commands, 11, 4, "nolimit : y");
	mvwprintw(env->commands, 13, 2, "Pause/Run : SPACE");
	wrefresh(env->commands);
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
	env->commands = subwin(stdscr, 16, 58, 52, 196);
	wborder(env->commands, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	attroff(A_REVERSE | A_STANDOUT | COLOR_PAIR(2));
	fill_commands(env);
	env->mem = subwin(stdscr, 64, 193, 2, 3);
	env->infos = subwin(stdscr, 53, 58, 2, 197);
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