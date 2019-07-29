/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_env *env, unsigned j)
{
	int index;

	env->process[j].op.name = "zjmp";
	if (env->process[j].carry == 1)
	{
		index = read_bytes(env->process[j].op.saved, 1, 2) % IDX_MOD;
		env->process[j].pc += index;
		if (env->process[j].pc < 0)
			env->process[j].pc += MEM_SIZE;
		else if (env->process[j].pc >= MEM_SIZE)
			env->process[j].pc %= MEM_SIZE;
	}
	else
		env->process[j].pc += 3;
}
