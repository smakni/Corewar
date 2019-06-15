/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/06/14 17:51:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, unsigned j)
{
	int index;

	env->proc[j].op.name = "jmp";
	if (env->proc[j].carry == 1)
	{
		index = read_bytes(env->proc[j].op.saved, 1, 2);
		env->proc[j].pc += index % IDX_MOD;
		if (env->proc[j].pc < 0)
			env->proc[j].pc += MEM_SIZE;
		else if (env->proc[j].pc >= MEM_SIZE)
			env->proc[j].pc %= MEM_SIZE;
	}
	else
		env->proc[j].pc += 3;
}
