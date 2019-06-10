/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/06/10 19:32:41 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	intro_game(t_env *env)
{
	unsigned i;

	i = 0;
	env->cycle_to_die = CYCLE_TO_DIE;
	ft_printf("Introducing contestants...\n");
	while (i < env->nb_champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
					env->live[i].header.prog_size, env->live[i].header.prog_name, 
					env->live[i].header.comment);
		i++;
	}
}

int check_live(t_env *env)
{
	unsigned i;
	unsigned total_lives;

	i = 0;
	total_lives = 0;
	while (i < env->nb_champs)
	{
		total_lives += env->champ[i].nb_live;
		i++;
	}
	if (total_lives >= NBR_LIVE)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		return (1);
	}
	return (0);
}

static int	move_pc(t_env *env, int j)
{
	if (env->champ[j].pc >= MEM_SIZE)
		env->champ[j].pc -= MEM_SIZE;
	else if (env->champ[j].pc < 0)
		env->champ[j].pc += MEM_SIZE;
	if (env->err_code != 0)
		return (FAIL);
	env->champ[j].cycles = check_cycles(env, j);
	ft_bzero(&(env->champ[j].op), sizeof(t_op));
	return (1);
}

static int	process_execution(t_env *env, unsigned j)
{
	if (env->champ[j].cycles == 1)
	{
		exec_op(env, j);
		if (move_pc(env, j) == FAIL)
			return (FAIL);
	}
	else if (env->champ[j].cycles > 1)
		env->champ[j].cycles--;
	return (1);
}

static int reset_cycles(t_env *env, int *check_delta)
{
	if (*check_delta == MAX_CHECKS)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		*check_delta = 0;
	}
	del_process(env);
	return (0);
}

int read_memory(t_env *env)
{
	int j;
	int i;
	int check_delta;

	j = 0;
	i = 0;
	check_delta = 0;
	intro_game(env);
	while (env->cycle_to_die > 0 && env->nb_champs > 0)
	{
		j = env->nb_champs - 1;
		ft_printf("It is now cycle %d\n", env->cycle_index + 1);
		while (j >= 0)
		{
			if (process_execution(env, j) == FAIL)
				return (FAIL);
			j--;
		}
		if (i == env->cycle_to_die)
		{
			if (check_live(env) == 0)
				check_delta++;
			i = reset_cycles(env, &check_delta);
		}
		if (env->visu == 1)
		{
			print_infos(env);
			key_events(env);
		}
		else
			ft_print_memory(env);
		//read(0, 0, 1);
		env->cycle_index++;
		i++;
	}
	return (SUCCESS);
}
