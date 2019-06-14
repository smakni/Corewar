#include "../../includes/vm.h"
#include <curses.h>

static int	count_live(t_env *env, unsigned j, int *nb_process)
{
	int			nb_live;
	unsigned	i;

	nb_live = 0;
	i = 0;
	while (i < env->nb_champs)
	{
		if (env->champ[i].id == UINT32_MAX - j && env->champ[i].nb_live >= 0)
			nb_live += env->champ[i].nb_live;
		if (env->champ[i].id == UINT32_MAX - j && env->champ[i].nb_live > -1)
			(*nb_process)++;
		i++;
	}
	return (nb_live);
}

void print_infos(t_env *env)
{
	int i;
	int	nb_live;
	int	nb_process;
	unsigned j;

	i = 0;
	j = 0;
	if (env->speed == 0)
		env->speed = 50;
	wattron(env->infos, COLOR_PAIR(3));
	mvwprintw(env->infos, i += 2, 2, "Cycles/second limit : %-10d", env->speed);
	mvwprintw(env->infos, i += 2, 2, "Cycle : %d", env->cycle_index);
	mvwprintw(env->infos, i += 2, 2, "Nb Processes : %-10d", env->nb_champs);
	i += 2;
	while (j < env->nb_player)
	{
		nb_process = 0;
		mvwprintw(env->infos, i, 2, "Player %d: ", j + 1);
		wattron(env->infos, COLOR_PAIR(4 + j));
		wprintw(env->infos, "%s", env->live[j].header.prog_name);
		i++;
		wattroff(env->infos, COLOR_PAIR(4 + j));
		mvwprintw(env->infos, i++, 4, "Last live : %d", env->live[j].last_live);
		nb_live = count_live(env, j, &nb_process);
		mvwprintw(env->infos, i, 4, "Total lives during current cycle : %-10d", nb_live);
		i++;
		mvwprintw(env->infos, i, 4, "NB processes : %-10d", nb_process);
		i += 2;
		j++;
	}
	mvwprintw(env->infos, i += 2, 2, "CYCLE_TO_DIE : %-5d", env->cycle_to_die);
	mvwprintw(env->infos, i += 2, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->infos, i += 2, 2, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->infos, i += 2, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(env->infos, COLOR_PAIR(3));
	wrefresh(env->infos);
	if (env->speed != -1)
		usleep(1000000 / env->speed);
}
