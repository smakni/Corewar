/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:04:01 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			op_len(t_env *env, unsigned j, int op)
{
	int tab_len[2];
	int	pc;

	if (op == 1 || op == 9 || op == 12 || op == 15)
	{
		tab_len[0] = 3;
		tab_len[1] = 5;
		return (tab_len[op % 3]);
	}
	pc = env->process[j].pc;
	if (op == 16)
		return (3);
	else if (op == 2 || op == 3 || op == 13)
		return (1 + decode_byte_param(env->memory[(pc + 1) % MEM_SIZE], 0, 2));
	else if (op == 10 || op == 11 || op == 14)
		return (1 + decode_byte_param(env->memory[(pc + 1) % MEM_SIZE], 1, 3));
	return (1 + decode_byte_param(env->memory[(pc + 1) % MEM_SIZE], 0, 3));
}

void		save_op(t_env *env, unsigned j)
{
	int len;
	int i;

	i = 0;
	len = op_len(env, j, env->process[j].op.code);
	while (i < len)
	{
		env->process[j].op.saved[i] = env->memory[(env->process[j].pc + i)
			% MEM_SIZE];
		i++;
	}
}
