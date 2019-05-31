/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/31 17:30:19 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, unsigned j)
{
	int index;

	if (env->champ[j].carry == 1)
	{
		index = read_bytes(env->memory, env->champ[j].pc + 1, 2);
		env->champ[j].pc += index;
		env->champ[j].pc %= MEM_SIZE;
	}
	else
		env->champ[j].pc += 3;
}