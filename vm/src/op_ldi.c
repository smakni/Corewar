/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:24:07 by smakni            #+#    #+#             */
/*   Updated: 2019/05/21 19:02:50 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ldi(t_env *env ,int j)
{
	int	v1;
	int	v2;
	int	reg;
	int to_store;
	int	cursor;

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	reg = env->memory[cursor + 1];
	if (type_param(env->memory[env->champ[j]. pc + 1], 1) == REG_CODE)
	{
		to_store = read_multi_bytes(env->memory,
				env->champ[j].pc + (v1 % IDX_MOD) + 1,
				1);
	}
	else
	{
		to_store = read_multi_bytes(env->memory,
				env->champ[j].pc + (v1 % IDX_MOD) + 2,
				IND_SIZE); 
	}
		to_store += v2;
		to_store = read_multi_bytes(env->memory,
				env->champ[j].pc + (to_store % IDX_MOD) + 3,
				REG_SIZE);
	//ft_printf("cursor = %i\n", env->champ[j].pc);
	//to_store = read_multi_bytes(env->memory, env->champ[j].pc + ((v1 + v2) % IDX_MOD) + 3, REG_SIZE);
	env->champ[j].r[reg] = to_store;
}

void		op_lldi(t_env *env ,int j)
{
	int	v1;
	int	v2;
	int	v3;
	int	to_store;
	//int	reg;
	int	cursor;

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	v3 = get_value_index(env, j, &cursor, 3);
	to_store = read_multi_bytes(env->memory,
				env->champ[j].pc + v1 + v2 + 4, REG_SIZE);
	env->champ[j].r[v3] = to_store;

}
