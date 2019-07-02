/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_live.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:29:58 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/02 19:31:18 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	last_visu_infos(t_env *env, int save)
{
	mvwprintw(env->state, 0, 0, "**Game Over**");
	mvwprintw(env->infos, 46, 0, "WINNER :");
	wattron(env->infos, COLOR_PAIR(4 + save));
	mvwprintw(env->infos, 46, 9, "%s", env->player[save].header.prog_name);
	wattroff(env->infos, COLOR_PAIR(4 + save));
	mvwprintw(env->infos, 44, 0, "env->nb_process:%d", env->nb_process);
	wrefresh(env->infos);
	wrefresh(env->state);
}

static void	del_visible_windows(t_env *env)
{
	delwin(env->mem);
	delwin(env->around_memory);
	if (env->option == 1)
	{
		delwin(env->state);
		delwin(env->commands);
		delwin(env->infos);
		delwin(env->around_infos);
		if (env->verb == 1)
		{
			delwin(env->verbos);
			delwin(env->around_verbos);
		}
	}
}

static void	last_visu(t_env *env, int save)
{
	int		i;

	if (env->option == 1)
		last_visu_infos(env, save);
	timeout(-1);
	while (1)
		if (getch())
		{
			i = 0;
			while (i < GO_BACK && i < env->cycle_index)
			{
				delwin(env->trace[i]);
				if (env->option == 1)
					delwin(env->traceinfos[i]);
				if (env->option == 1 && env->verb == 1)
					delwin(env->traceverbos[i]);
				i++;
			}
			del_visible_windows(env);
			curs_set(1);
			endwin();
			break ;
		}
}

int			check_last_live(t_env *env)
{
	int	i;
	int	save;
	int	last_live;

	i = env->nb_player - 1;
	save = i;
	last_live = 0;
	while (i >= 0)
	{
		if (env->player[i].last_live >= last_live
				&& env->player[i].last_live != 0)
		{
			last_live = env->player[i].last_live;
			save = i;
		}
		i--;
	}
	if (env->option == 1 || env->option == 2)
		last_visu(env, save);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n", save + 1,
				env->player[save].header.prog_name);
	return (save);
}
