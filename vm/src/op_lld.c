/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/05 15:08:29 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_lld(t_env *env ,unsigned j)
{
	int r_index;
	int	to_store;
	int	param_1;

	env->champ[j].op.name = "lld";
	env->champ[j].op.nb_params = 2;
	param_1 = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
	{
		to_store = read_bytes(env->memory, env->champ[j].pc + 2, 2);
		//ft_printf("DIRECT>>param_1 = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 6];
	}
	else
	{
		param_1 = read_bytes(env->memory, env->champ[j].pc + 2, 2);
		//ft_printf("INDIRECT>mem_index = %d\n", param_1);
		r_index = env->memory[env->champ[j].pc + 4];
		to_store = read_bytes(env->memory, env->champ[j].pc + (param_1), 4);
	}
	if (to_store == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[r_index] = to_store;
	//ft_printf("r[%d] = %x\n", r_index, env->champ[j].r[r_index]);
	env->champ[j].pc += 1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0);
}
