/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:04:01 by smakni            #+#    #+#             */
/*   Updated: 2019/06/13 19:18:37 by smakni           ###   ########.fr       */
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
		return (1 + decode_byte_param(env->memory[env->proc[j].pc +1], 0, 2));
	else if (op == 10 || op == 11 || op == 14)
		return (1 + decode_byte_param(env->memory[env->proc[j].pc + 1], 1, 3));
	return (1 + decode_byte_param(env->memory[env->proc[j].pc + 1], 0, 3));
}

void		save_op(t_env *env, unsigned j)
{
	int op;
	int len;
	int i;

	i = 0;
	op = (int)env->memory[env->proc[j].pc];
	len = op_len(env, j, op);
	//ft_printf("%s\n", &env->memory[env->proc[j].pc]);
	while (i < len)
	{
		env->proc[j].op.saved[i] = env->memory[(env->proc[j].pc + i) % MEM_SIZE];
		i++;
	}
	//ft_memcpy(env->proc[j].op.saved, &env->memory[env->proc[j].pc], op_len(env, j, op));
}
