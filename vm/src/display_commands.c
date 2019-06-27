/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:51:41 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/17 18:52:06 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static void		protect_mvwprintw(t_env *env, int y, int x, char *str)
{
	if (mvwprintw(env->commands, y, x, str) == ERR)
		exit_clean(env);
}

void			fill_commands_mv_back(t_env *env)
{
	protect_werase(env, env->commands);
	wattrset(env->commands, A_NORMAL | COLOR_PAIR(3));
	protect_mvwprintw(env, 1, 2, "COMMANDS :");
	protect_mvwprintw(env, 3, 2, "Press 'p' to quit exploration mode");
	protect_mvwprintw(env, 5, 2, "Cycle -= 10 : 'h'");
	protect_mvwprintw(env, 6, 2, "Cycle -= 1 : 'j'");
	protect_mvwprintw(env, 7, 2, "Cycle += 1 : 'k'");
	protect_mvwprintw(env, 8, 2, "Cycle += 10 : 'l'");
	protect_mvwprintw(env, 10, 2, "Cannot move in future cycles");
	if (mvwprintw(env->commands, 12, 2,
		"Cannot move back more than %d cycles",	GO_BACK) == ERR)
		exit_clean(env);
	if (wattron(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT) == ERR)
		exit_clean(env);
	if (wborder(env->commands, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ') == ERR)
		exit_clean(env);
	if (wattroff(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT) == ERR)
		exit_clean(env);
	protect_wrefresh(env, env->commands);
}

void			fill_commands(t_env *env)
{
	protect_werase(env, env->commands);
	wattrset(env->commands, A_NORMAL | COLOR_PAIR(3));
	protect_mvwprintw(env, 1, 2, "COMMANDS :");
	protect_mvwprintw(env, 3, 2, "Press any key to launch/quit");
	protect_mvwprintw(env, 5, 2, "Speed :");
	protect_mvwprintw(env, 6, 4, "-10 cycles/second : q");
	protect_mvwprintw(env, 7, 4, "-1 cycle/second : w");
	protect_mvwprintw(env, 8, 4, "+1 cycle/second : e");
	protect_mvwprintw(env, 9, 4, "+10 cycle/second : r");
	protect_mvwprintw(env, 10, 4, "cycle/second = 1 : t");
	protect_mvwprintw(env, 11, 4, "nolimit : y");
	protect_mvwprintw(env, 12, 2, "Pause/Run : SPACE");
	if (env->goback == 1)
		protect_mvwprintw(env, 14, 2, "Exploration mode : 'p'");
	if (wattron(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT) == ERR)
		exit_clean(env);
	if (wborder(env->commands, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ') == ERR)
		exit_clean(env);
	if (wattroff(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT) == ERR)
		exit_clean(env);
	protect_wrefresh(env, env->commands);
}
