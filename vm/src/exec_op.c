/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/05/22 01:02:15 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int 	decode_byte_param(unsigned char param, int is_index)
{
	int		op_len;
	char	mask;
	int		i;
	char	tmp;

	op_len = 1;
	i = 0;
	mask = 0b00000011;
	while (i < 4)
	{
		tmp = mask & param >> (i * 2);
		if (tmp == 1)
			op_len++;
		else if (tmp == 2)
		{
			if (is_index)
				op_len += 2;
			else
				op_len += 4;
		}
		else if (tmp == 3)
			op_len += 2;
		i++;
	}
	return (op_len);
}

int		exec_op(t_env *env, int j)
{
	if (env->memory[env->champ[j].pc] == 0x01)
	{	
		ft_printf("live\n");
		op_live(env, j);
		return (5);
	}
	else if (env->memory[env->champ[j].pc] == 0x02)
	{
		ft_printf("ld\n");
		op_ld(env, j);
		ft_printf("r5 = %x\n", env->champ[j].r[5]);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x03)
	{
		ft_printf("st\n");
		op_st(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x04)
	{
		ft_printf("add\n");
		op_add(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x05)
	{
		ft_printf("sub\n");
		op_sub(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x06)
	{
		ft_printf("and\n");
		op_and(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x07)
	{
		ft_printf("or\n");
		op_or(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x08)
	{
		ft_printf("xor\n");
		op_xor(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x09)
	{
		ft_printf("zjump\n");
		op_zjmp(env, j);
		return (3); //return address of the jump
	}
	else if (env->memory[env->champ[j].pc] == 0x0a)
	{
		ft_printf("ldi\n");
	//	op_ldi(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
	}
	else if (env->memory[env->champ[j].pc] == 0x0b)
	{
		ft_printf("sti\n");
		op_sti(env, j);
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
	}
	else if (env->memory[env->champ[j].pc] == 0x0c)
	{
		ft_printf("fork\n");
		op_fork(env, j);
		return (3);
	}
	else if (env->memory[env->champ[j].pc] == 0x0d)
	{
		ft_printf("lld\n");
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	else if (env->memory[env->champ[j].pc] == 0x0e)
	{
		ft_printf("lldi\n");
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 1));
	}
	else if (env->memory[env->champ[j].pc] == 0x0f)
	{
		ft_printf("lfork\n");
		return (3);
	}
	else if (env->memory[env->champ[j].pc] == 0x10)
	{
		ft_printf("aff\n");
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
	}
	return (1);
}
