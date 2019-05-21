/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/21 17:05:33 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

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
	while (rounds < 4)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			debug = 0;
			ft_printf(">>READ_CHAMP[%d]<<PC>>[%d]\n", j, env->champ[j].pc);
			ft_printf(">>>TO_WAIT>>>[%2d]\n", env->champ[j].cycles);
			if (env->champ[j].cycles == 0)
			{
				op_len = exec_op(env, j);
				if (env->champ[j].pc >= MEM_SIZE)
					env->champ[j].pc -= MEM_SIZE;
				else
					env->champ[j].pc += op_len;
				env->champ[j].cycles = check_cycles(env, j);
			}
			else
				env->champ[j].cycles--;
			usleep(10000);
			j++;
		}
		if (i == 100) //CYCLE_TO_DIE
		{
			rounds++;
			i = 0;
			ft_printf("ROUND[%3d]\n", rounds);
			// usleep(500000);
		}
		ft_print_memory(env);
		read(0, 0, 1);
		i++;
	}
	return (0);
}