/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/22 16:15:36 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, int j)
{
	int index;

	env->champ[j].carry = 1;
	if (env->champ[j].carry == 1)
	{
		index =  env->memory[env->champ[j].pc + 1] - env->memory[env->champ[j].pc + 2] + 1;
		ft_printf("INDEX_JUMP = %d\n", index);
		env->champ[j].pc -= index % IDX_MOD;
	}
	env->champ[j].carry = 0;
}