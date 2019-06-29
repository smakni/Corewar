/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection_visu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 11:33:36 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/28 11:34:25 by vrenaudi         ###   ########.fr       */
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
