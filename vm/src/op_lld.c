/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/23 23:24:09 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_lld(t_env *env ,int j)
{
	int r_index;
	int	to_store;
	int	param_1;

	param_1 = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
	{
		to_store = read_bytes(env, env->champ[j].pc + 2);
		//ft_printf("DIRECT>>param_1 = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 6];
	}
	else
	{
		param_1 = read_multi_bytes(env->memory, env->champ[j].pc + 3, 2);
		//ft_printf("INDIRECT>mem_index = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 4];
		to_store = read_bytes(env, env->champ[j].pc + (param_1));
	}
	//ft_printf("to_store = %x\n", to_store);
	//ft_printf("r = %d\n", r_index);
	env->champ[j].r[r_index] = to_store;
	//ft_printf("r[%d] = %x\n", r_index, env->champ[j].r[r_index]);
	env->champ[j].carry = 1;
	env->champ[j].pc += 1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0);
}
