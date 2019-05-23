/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/22 13:43:00 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_live(t_env *env)
{
	int i;
	int total_lives;

	i = 0;
	while (i < env->nb_champs)
	{
		if (total_lives >= NBR_LIVE)
		{
			env->cycle_to_die -= CYCLE_DELTA;
			return (1);
		}
		total_lives = env->champ_live[i++];
	}
	return (0);
}

static int	reset_cycles(t_env *env)
{
	env->cycle_to_die -= 500;
	check_live(env);
	// del_process(env);
	ft_print_memory(env);
	//check_last_live for winner
	if (env->cycle_to_die <= 0)
	{
		ft_printf(">>>>>>>>>>>>>>END_PROG<<<<<<<<<<<<<\n");
		return (0);
	}
	return (1);
}	

int		read_memory(t_env *env)
{
	int				j;
	int				i;
	int 			rounds;
	// int				op_len;
	int				check_delta;

	j = 0;
	rounds = 1;
	check_delta = 0;
	env->cycle_to_die = CYCLE_TO_DIE;
	i = 0;
	ft_printf("ROUND[%3d]\n", rounds);
	while (env->cycle_to_die > 0)
	{
		j = 0;
		ft_printf("CTD>>>>>>>>>>>>>>[%d]<<<<<<<<<<<<<<[%d]\n", env->cycle_index, env->cycle_to_die);
		while (j < env->nb_champs)
		{
			ft_printf("CHAMP[%d]<<PC[%d]\n", j, env->champ[j].pc);
			ft_printf("[%2d]\n", env->champ[j].cycles);
			if (env->champ[j].cycles == -24)
				exit (0);
			if (env->champ[j].cycles == 0)
			{
				exec_op(env, j);
				if (env->champ[j].pc >= MEM_SIZE)
					env->champ[j].pc -= MEM_SIZE;
				// env->champ[j].pc += op_len;
				env->champ[j].cycles = check_cycles(env, j);
			}
			else if (env->champ[j].cycles > 0)
				env->champ[j].cycles--;
			j++;
		}
		if (i == env->cycle_to_die) //CYCLE_TO_DIE - DELTA
		{
			if ((i = reset_cycles(env)) == 0)
				check_delta++;
			else
				i = 0;
			if (check_delta == MAX_CHECKS)
			{
				env->cycle_to_die -= CYCLE_DELTA;
				check_delta = 0;
			}
			ft_printf("ROUND[%3d]\n", rounds);
			rounds++;
		}
		ft_print_memory(env);
		read(0, 0, 1);
		env->cycle_index++;
		i++;
	}
	return (0);
}