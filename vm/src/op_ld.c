/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/04 23:05:00 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ld(t_env *env ,unsigned j)
{
	int r_index;
	int	to_store;
	int	param_1;

	param_1 = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
	{
		to_store = read_bytes(env->memory, env->champ[j].pc + 2, 4);
		r_index = env->memory[env->champ[j].pc + 6];
	}
	else
	{
		param_1 = read_bytes(env->memory, env->champ[j].pc + 2, 2);
		r_index = env->memory[env->champ[j].pc + 4];
		to_store = read_bytes(env->memory, env->champ[j].pc + (param_1 % IDX_MOD), 4);
	}
	if (to_store == 0 && r_index >= 1 && r_index <= 16)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	if (r_index >= 1 && r_index <= 16)
		env->champ[j].r[r_index] = to_store;
	env->champ[j].pc += 1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0);
}
