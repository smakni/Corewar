/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:04:01 by smakni            #+#    #+#             */
/*   Updated: 2019/06/21 16:52:11 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			op_len(t_env *env, unsigned j, int op)
{
	int tab_len[2];

	if (op == 1 || op == 9 || op == 12 || op == 15)
	{
		tab_len[0] = 3;
		tab_len[1] = 5;
		return (tab_len[op % 3]);
	}
	if (op == 16)
		return (3);
	else if (op == 2 || op == 3 || op == 13)
		return (1 + decode_byte_param(env->memory[env->process[j].pc +1], 0, 2));
	else if (op == 10 || op == 11 || op == 14)
		return (1 + decode_byte_param(env->memory[env->process[j].pc + 1], 1, 3));
	return (1 + decode_byte_param(env->memory[env->process[j].pc + 1], 0, 3));
}

void		save_op(t_env *env, unsigned j)
{
	int len;
	int i;

	i = 0;
	len = op_len(env, j, env->process[j].op.code);
	env->process[j].op.len = len;
	//ft_printf("%s\n", &env->memory[env->process[j].pc]);
	while (i < len)
	{
		env->process[j].op.saved[i] = env->memory[(env->process[j].pc + i) % MEM_SIZE];
		i++;
	}
	//ft_memcpy(env->process[j].op.saved, &env->memory[env->process[j].pc], op_len(env, j, op));
}
