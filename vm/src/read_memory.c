/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/20 02:54:47 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		read_memory(t_env *env)
{
	int i;
	int	j;
	int rounds;
	int	read;
	int	op_len;

	i = 0;
	j = 0;
	rounds = 1;
	ft_printf("ROUND[%3d]\n", rounds);
	while (rounds <= 10)
	{
		//for each champ
		//check if cicles to wait = 0
		//if = 0
		//read memory from pc
		//save op_len
		//exec op >> check if op exec at cycle = 0 or first cycle
		//exec op
		//check if carry change
		//pc += op_len
		j = 0;
		while (j < env->nb_champs)
		{
			ft_printf(">>READ_CHAMP[%d]<<\n", j);
			read = 0;	//check op len
			if (env->champ[j].cycles == 0)
			{
				op_len = 10;
				while(read < op_len) //check op len
				{
					ft_printf("read_champ[%d]>>[%.2x]\n", j, env->memory[env->champ[j].pc++]);
					read++;
				}
			}
			//env->champ[j].pc += 4; // += op_len
			usleep(500000);
			j++;
		}
		if (i == 10) //CYCLE_TO_DIE
		{
			rounds++;
			ft_printf("ROUND[%3d]\n", rounds);
			usleep(500000);
			i = 0;
		}
		i++;
	}
	return (0);
}