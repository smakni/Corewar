/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/22 17:18:46 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	read_bytes(t_env *env, int index)
{
	int	ret;

	ret = 0;
	ret += env->memory[index] << 24;
	ret += env->memory[index + 1] << 16;
	ret += env->memory[index + 2] << 8;
	ret += env->memory[index + 3];
	return (ret);
}

void		op_ld(t_env *env ,int j)
{
	int r_index;
	int	to_store;
	int	param_1;

	param_1 = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
	{
		to_store = read_bytes(env, env->champ[j].pc + 2);
		ft_printf("DIRECT>>param_1 = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 6];
	}
	else
	{
		param_1 = read_multi_bytes(env->memory, env->champ[j].pc + 3, 2);
		ft_printf("INDIRECT>mem_index = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 4];
		to_store = read_bytes(env, env->champ[j].pc + (param_1 % IDX_MOD));
	}
	ft_printf("to_store = %x\n", to_store);
	ft_printf("r = %d\n", r_index);
	env->champ[j].r[r_index] = to_store;
	ft_printf("r[%d] = %x\n", r_index, env->champ[j].r[r_index]);
	env->champ[j].carry = 1;
}
