/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:29:55 by sabri             #+#    #+#             */
/*   Updated: 2019/05/20 12:28:45 by smakni           ###   ########.fr       */
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

int		exec_op(t_env *env, int j)
{
	if (env->memory[env->champ[j].pc] == 0x01)
		ft_printf("live\n");
	else if (env->memory[env->champ[j].pc] == 0x02)
		ft_printf("ld\n");
	else if (env->memory[env->champ[j].pc] == 0x03)
		ft_printf("st\n");
	else if (env->memory[env->champ[j].pc] == 0x04)
		ft_printf("add\n");
	else if (env->memory[env->champ[j].pc] == 0x05)
		ft_printf("sub\n");
	else if (env->memory[env->champ[j].pc] == 0x06)
		ft_printf("and\n");
	else if (env->memory[env->champ[j].pc] == 0x07)
		ft_printf("or\n");
	else if (env->memory[env->champ[j].pc] == 0x08)
		ft_printf("xor\n");
	else if (env->memory[env->champ[j].pc] == 0x09)
		ft_printf("zjump\n");
	else if (env->memory[env->champ[j].pc] == 0x0a)
		ft_printf("ldi\n");
	else if (env->memory[env->champ[j].pc] == 0x0b)
		ft_printf("sti\n");
	else if (env->memory[env->champ[j].pc] == 0x0c)
		ft_printf("fork\n");
	else if (env->memory[env->champ[j].pc] == 0x0d)
		ft_printf("lld\n");
	else if (env->memory[env->champ[j].pc] == 0x0e)
		ft_printf("lldi\n");
	else if (env->memory[env->champ[j].pc] == 0x0f)
		ft_printf("lfork\n");
	else if (env->memory[env->champ[j].pc] == 0x10)
		ft_printf("aff\n");
	return (1);
}

int		read_memory(t_env *env)
{
	int 			i;
	int				j;
	int 			rounds;
	int				op_len;

	i = 0;
	j = 0;
	rounds = 1;
	ft_printf("ROUND[%3d]\n", rounds);
	while (rounds <= 5)
	{
		j = 0;
		while (j < env->nb_champs)
		{
			ft_printf(">>READ_CHAMP[%d]<<\n", j);
			if (env->champ[j].cycles == 0)
				op_len = exec_op(env, j);
			env->champ[j].pc += op_len;
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