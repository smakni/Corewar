/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/21 16:48:35 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, int j)
{
	int index;

	if (env->champ[j].carry == 1)
	{
		index = read_multi_bytes(env->memory, env->champ[j].pc + IND_SIZE + 1, IND_SIZE);
		env->champ[j].pc = index;
	}
	env->champ[j].carry = 0;
}