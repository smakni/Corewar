/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:51:41 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			fill_commands_mv_back(t_env *env)
{
	protect_werase(env, env->commands);
	wattrset(env->commands, A_NORMAL | COLOR_PAIR(3));
	mvwprintw(env->commands, 1, 2, "COMMANDS :");
	mvwprintw(env->commands, 3, 2, "Press 'p' to quit exploration mode");
	mvwprintw(env->commands, 5, 2, "Cycle -= 10 : 'h'");
	mvwprintw(env->commands, 6, 2, "Cycle -= 1 : 'j'");
	mvwprintw(env->commands, 7, 2, "Cycle += 1 : 'k'");
	mvwprintw(env->commands, 8, 2, "Cycle += 10 : 'l'");
	mvwprintw(env->commands, 10, 2, "Cannot move in future cycles");
	if (mvwprintw(env->commands, 12, 2,
			"Cannot move back more than %d cycles", GO_BACK - 1) == ERR)
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
	mvwprintw(env->commands, 1, 2, "COMMANDS :");
	mvwprintw(env->commands, 3, 2, "Press any key to launch/quit");
	mvwprintw(env->commands, 5, 2, "Speed :");
	mvwprintw(env->commands, 6, 4, "-10 cycles/second : q");
	mvwprintw(env->commands, 7, 4, "-1 cycle/second : w");
	mvwprintw(env->commands, 8, 4, "+1 cycle/second : e");
	mvwprintw(env->commands, 9, 4, "+10 cycle/second : r");
	mvwprintw(env->commands, 10, 4, "cycle/second = 1 : t");
	mvwprintw(env->commands, 11, 4, "nolimit : y");
	mvwprintw(env->commands, 12, 2, "Pause/Run : SPACE");
	if (env->goback == 1)
		mvwprintw(env->commands, 14, 2, "Exploration mode : 'p'");
	wattron(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
	wborder(env->commands, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(env->commands, COLOR_PAIR(2) | A_REVERSE | A_STANDOUT);
	protect_wrefresh(env, env->commands);
}
