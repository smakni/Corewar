/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection_visu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 11:33:36 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
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
	delwin(env->mem);
	delwin(env->around_memory);
	if (env->option == 1)
	{
		delwin(env->infos);
		delwin(env->around_infos);
		delwin(env->state);
		delwin(env->commands);
		if (env->verb == 1)
		{
			delwin(env->verbos);
			delwin(env->around_verbos);
		}
	}
	curs_set(1);
	endwin();
	exit(-1);
}
