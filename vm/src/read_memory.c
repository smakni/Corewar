/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/29 15:24:40 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_live(t_env *env)
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
		return (1);
	}
	return (0);
}

static int	reset_cycles(t_env *env)
{
	del_process(env);
	if (env->cycle_to_die <= 0)
		return (0);
	return (1);
}	

void		aff_memory(t_env *env, unsigned j, int len)
{
	int i;

	i = 0;
	ft_printf("op>>[ ");
	while (i < len)
	{
		ft_printf("%.2x ", env->memory[env->champ[j].pc + i]);
		ft_printf("i = %d\n", i);
		i++;
	}
	ft_printf("]\n");
}

int		read_memory(t_env *env)
{
	unsigned		j;
	int				i;
	int				check_delta;

	j = 0;
	check_delta = 0;
	env->cycle_to_die = CYCLE_TO_DIE;
	i = 0;
	while (env->cycle_to_die > 0 && env->nb_champs > 0)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			if (env->champ[j].cycles == 0)
			{
				exec_op(env, j);
				if (env->champ[j].pc >= MEM_SIZE)
					env->champ[j].pc -= MEM_SIZE;
				else if (env->champ[j].pc < 0)
					env->champ[j].pc += MEM_SIZE;
				if (env->err_code != 0)
					return (FAIL);
				env->champ[j].cycles = check_cycles(env, j);
			}
			else if (env->champ[j].cycles > 0)
				env->champ[j].cycles--;
			j++;
		}
		if (i == env->cycle_to_die)
		{
			if ((i = check_live(env)) == 0)
				check_delta++;
			i = 0;
			reset_cycles(env);
			if (check_delta == MAX_CHECKS)
			{
				env->cycle_to_die -= CYCLE_DELTA;
				check_delta = 0;
			}
		}
		ft_print_memory(env);
		print_infos(env);
	if (env->cycle_index == 1)
		timeout(0);
	if (env->cycle_index > 0 && getch() == ' ')
	{
		while (1)
			if (getch() == ' ')
				break;
	}
		//read(0, 0, 1);
		env->cycle_index++;
		i++;
	}
	return (SUCCESS);
}