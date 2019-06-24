/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvback.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:55:04 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/24 11:56:47 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

void 	mv_back(t_env *env)
{
	int key;
	int where;
	int cycle;

	if (env->option == 1)
	{
		mvwprintw(env->state, 0, 0, "EXPLORATION MODE");
		wrefresh(env->state);
		fill_commands_mv_back(env);
	}
	where = env->cycle_index % GO_BACK;
	cycle = env->cycle_index;
	while (1)
	{
		key = getch();
		if (key == 'p')
		{
			overlay(env->trace[env->cycle_index % GO_BACK], env->mem);
			wrefresh(env->mem);
			if (env->option == 1)
			{
				fill_commands(env);
				overwrite(env->traceinfos[env->cycle_index % GO_BACK], env->infos);
				wrefresh(env->infos);
			}
			break;
		}
		else if (key == 'h' && cycle > env->cycle_index - GO_BACK - 10 && cycle > 9)
		{
			where -= 10;
			cycle -= 10;
			if (where < 0)
				where += GO_BACK;
			overlay(env->trace[where], env->mem);
			wrefresh(env->mem);
			if (env->option == 1)
			{
				overwrite(env->traceinfos[where], env->infos);
				wrefresh(env->infos);
			}
		}
		else if (key == 'j' && cycle > env->cycle_index - GO_BACK && cycle > 0)
		{
			where -= 1;
			cycle -= 1;
			if (where < 0)
				where += GO_BACK;
			overlay(env->trace[where], env->mem);
			wrefresh(env->mem);
			if (env->option == 1)
			{
				overwrite(env->traceinfos[where], env->infos);
				wrefresh(env->infos);
			}
		}
		else if (key == 'k' && cycle < env->cycle_index)
		{
			where += 1;
			cycle += 1;
			if (where >= GO_BACK)
				where -= GO_BACK;
			overlay(env->trace[where], env->mem);
			wrefresh(env->mem);
			if (env->option == 1)
			{
				overwrite(env->traceinfos[where], env->infos);
				wrefresh(env->infos);
			}
		}
		else if (key == 'l' && cycle < env->cycle_index - 9)
		{
			where += 10;
			cycle += 10;
			if (where >= GO_BACK)
				where -= GO_BACK;
			overlay(env->trace[where], env->mem);
			wrefresh(env->mem);
			if (env->option == 1)
			{
				overwrite(env->traceinfos[where], env->infos);
				wrefresh(env->infos);
			}
		}
	}
}
