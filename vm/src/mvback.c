/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvback.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:55:04 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/29 12:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static void		exit_explo_mode(t_env *env)
{
	overlay(env->trace[env->cycle_index % GO_BACK], env->mem);
	protect_wrefresh(env, env->mem);
	if (env->option == 1)
	{
		fill_commands(env);
		overwrite(env->traceinfos[env->cycle_index % GO_BACK],
			env->infos);
		protect_wrefresh(env, env->infos);
		if (env->verb == 1)
		{
			overwrite(env->traceverbos[env->cycle_index % GO_BACK],
				env->verbos);
			protect_wrefresh(env, env->verbos);
		}
	}
}

static void		travel(t_env *env, int *where, int *cycle, int mv)
{
	*where += mv;
	*cycle += mv;
	if (*where < 0)
		*where += GO_BACK;
	else if (*where >= GO_BACK)
		*where -= GO_BACK;
	overlay(env->trace[*where], env->mem);
	protect_wrefresh(env, env->mem);
	if (env->option == 1)
	{
		overwrite(env->traceinfos[*where], env->infos);
		protect_wrefresh(env, env->infos);
		if (env->verb == 1)
		{
			overwrite(env->traceverbos[*where], env->verbos);
			protect_wrefresh(env, env->verbos);
		}
	}
}

static void		while_mv_back(t_env *env, int key, int where, int cycle)
{
	while (1)
	{
		key = getch();
		if (key == 'p')
		{
			exit_explo_mode(env);
			break ;
		}
		else if (key == 'h' && cycle > env->cycle_index - GO_BACK + 10
			&& cycle > 9)
			travel(env, &where, &cycle, -10);
		else if (key == 'j' && cycle > env->cycle_index - GO_BACK + 1
				&& cycle > 0)
			travel(env, &where, &cycle, -1);
		else if (key == 'k' && cycle < env->cycle_index)
			travel(env, &where, &cycle, 1);
		else if (key == 'l' && cycle < env->cycle_index - 9)
			travel(env, &where, &cycle, 10);
	}
}

void			mv_back(t_env *env)
{
	int key;
	int where;
	int cycle;

	key = 0;
	if (env->option == 1)
	{
		mvwprintw(env->state, 0, 0, "EXPLORATION MODE");
		protect_wrefresh(env, env->state);
		fill_commands_mv_back(env);
	}
	where = env->cycle_index % GO_BACK;
	cycle = env->cycle_index;
	while_mv_back(env, key, where, cycle);
}
