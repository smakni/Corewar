/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/20 13:50:33 by smakni           ###   ########.fr       */
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

	i = 0;
	j = 0;
	rounds = 1;
	ft_printf("ROUND[%3d]\n", rounds);
	while (rounds <= 5)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			debug = 0;
			ft_printf(">>READ_CHAMP[%d]<<\n", j);
			if (env->champ[j].cycles == 0)
				op_len = exec_op(env, j);
			while (debug < op_len)
			{
				ft_printf("read = %.2x\n",env->memory[env->champ[j].pc++]);
				debug++;
			}
			//env->champ[j].pc += op_len;
			usleep(500000);
			j++;
		}
		if (i == 100) //CYCLE_TO_DIE
		{
			rounds++;
			i = 0;
			ft_printf("ROUND[%3d]\n", rounds);
			usleep(500000);
		}
		i++;
	}
	return (0);
}