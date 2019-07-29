/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:11:58 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		intro_game(t_env *env)
{
	unsigned i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < env->nb_process)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
			env->player[i].header.prog_size,
				env->player[i].header.prog_name, env->player[i].header.comment);
		i++;
	}
}

static int		check_live(t_env *env, int *check_delta)
{
	int living_process;

	living_process = del_processess(env);
	if (env->live_period >= NBR_LIVE)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env->option == 0 && env->verb == 1)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		*check_delta = 0;
	}
	else
		(*check_delta)++;
	env->live_period = 0;
	return (living_process);
}

static int		reset_cycles(t_env *env, int *check_delta)
{
	if (*check_delta == MAX_CHECKS)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env->option == 0 && env->verb == 1)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		*check_delta = 0;
	}
	return (0);
}

int				while_playing(t_env *env, int i, int check_delta)
{
	while (env->living_proc > 0)
	{
		if (i == env->cycle_to_die || env->cycle_to_die < 0)
		{
			check_live(env, &check_delta);
			i = reset_cycles(env, &check_delta);
		}
		if (env->option == 0 && env->verb == 1 && env->living_proc > 0)
			ft_printf("It is now cycle %d\n", env->cycle_index);
		if (processess_execution(env) == FAIL)
			return (FAIL);
		if (env->option == 1 || env->option == 2)
			read_memory_visu(env);
		else if (env->option == 3 && env->cycle_index == env->dump)
		{
			ft_print_memory(env);
			exit(EXIT_SUCCESS);
		}
		env->cycle_index++;
		i++;
	}
	return (SUCCESS);
}

int				read_memory(t_env *env)
{
	int i;
	int check_delta;

	i = 0;
	check_delta = 0;
	if (env->option == 1)
	{
		print_infos(env);
		key_events(env);
	}
	else if (env->option == 2)
		key_events(env);
	env->cycle_index = 1;
	env->cycle_to_die = CYCLE_TO_DIE;
	if (env->option == 0 || env->option == 3)
		intro_game(env);
	if (while_playing(env, i, check_delta) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
