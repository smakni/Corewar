/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/05/22 13:35:31 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		exec_op(t_env *env, int j)
{
	void	(*op_fun[16])(t_env*, int);
	int		index;

	op_fun[0] = op_live;
	op_fun[1] = op_ld;
	op_fun[2] = op_st;
	op_fun[3] = op_add;
	op_fun[4] = op_sub;
	op_fun[5] = op_and;
	op_fun[6] = op_or;
	op_fun[7] = op_xor;
	op_fun[8] = op_zjmp;
	op_fun[9] = op_ldi;
	op_fun[10] = op_sti;
	op_fun[11] = op_fork;
	op_fun[12] = op_lld;
	op_fun[13] = op_lldi;
	op_fun[14] = op_lfork;
	op_fun[15] = op_aff;
	index = env->memory[env->champ[j].pc];
	if (index >= 0x01 && index <= 0x10)
		op_fun[index](env, j);
	else
		env->champ[j].pc++;
}

// int		exec_op(t_env *env, int j)
// {
// 	if (env->memory[env->champ[j].pc] == 0x01)
// 	{	
// 		ft_printf("live\n");
// 		op_live(env, j);
// 		return (5);
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x02)
// 	{
// 		ft_printf("ld\n");
// 		op_ld(env, j);
// 		ft_printf("r5 = %x\n", env->champ[j].r[5]);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x03)
// 	{
// 		ft_printf("st\n");
// 		op_st(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x04)
// 	{
// 		ft_printf("add\n");
// 		op_add(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x05)
// 	{
// 		ft_printf("sub\n");
// 		op_sub(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x06)
// 	{
// 		ft_printf("and\n");
// 		op_and(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x07)
// 	{
// 		ft_printf("or\n");
// 		op_or(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x08)
// 	{
// 		ft_printf("xor\n");
// 		op_xor(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x09)
// 	{
// 		ft_printf("zjump\n");
// 		op_zjmp(env, j);
// 		return (0); //return address of the jump
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0a)
// 	{
// 		ft_printf("ldi\n");
// 		op_ldi(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0b)
// 	{
// 		ft_printf("sti\n");
// 		op_sti(env, j);
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0c)
// 	{
// 		ft_printf("fork\n");
// 		op_fork(env, j);
// 		return (3);
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0d)
// 	{
// 		ft_printf("lld\n");
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0e)
// 	{
// 		ft_printf("lldi\n");
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x0f)
// 	{
// 		ft_printf("lfork\n");
// 		return (3);
// 	}
// 	else if (env->memory[env->champ[j].pc] == 0x10)
// 	{
// 		ft_printf("aff\n");
// 		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
// 	}
// 	return (1);
// }
