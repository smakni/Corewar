/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/21 00:45:01 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

//for each champ
//check if cicles to wait = 0
//if = 0
//read memory from pc
//save op_len
//exec op >> check if op exec at cycle = 0 or first cycle
//exec op
//check if carry change
//pc += op_len

int		read_memory(t_env *env)
{
	int 			i;
	int				j;
	int 			rounds;
	int				op_len;
	int				debug;
	t_fork 			*fork;

	i = 0;
	j = 0;
	rounds = 1;
	fork = NULL;
	ft_printf("ROUND[%3d]\n", rounds);
	// env->memory[20] = 255;
	// env->memory[21] = 255;
	// env->memory[22] = 255;
	// env->memory[23] = 255;
	while (rounds < 4)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			debug = 0;
			//ft_printf(">>READ_CHAMP[%d]<<PC>>[%d]\n", j, env->champ[j].pc);
			if (env->champ[j].cycles == 0)
				op_len = exec_op(env, j, &fork);
			if (env->champ[j].pc >= MEM_SIZE)
				env->champ[j].pc -= MEM_SIZE;
			else
				env->champ[j].pc += op_len;
			//usleep(1000);
			j++;
		}
		if (i == 10) //CYCLE_TO_DIE
		{
			rounds++;
			i = 0;
			ft_printf("ROUND[%3d]\n", rounds);
			//usleep(500000);
		}
		i++;
	}
	return (0);
}