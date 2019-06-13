/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/06/13 17:51:58 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, unsigned j)
{
	int index;
	int	save;

	env->champ[j].op.name = "jmp";
	save = env->champ[j].pc;
	if (env->champ[j].carry == 1)
	{
		index = read_bytes(env->champ[j].op.saved, 1, 2);
		env->champ[j].pc += index % IDX_MOD;
	}
	else
		env->champ[j].pc += 3;
}
