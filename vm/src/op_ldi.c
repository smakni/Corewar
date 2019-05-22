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

static int	read_ind_size_bytes(t_env *env, int index)
{
	int	ret;

	ret = 0;
	ret += env->memory[index] << 8;
	ret += env->memory[index + 1];
	return (ret);
}

void		op_ldi(t_env *env, int j)
{
	int	v1;
	int	v2;
	int	reg;
	int sum;
	int	cursor;

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	reg = env->memory[cursor + 1];
	ft_printf("v1, v2, reg = %i, %x, %i\n", v1, v2, reg);
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == IND_CODE)
		sum = read_ind_size_bytes(env, env->champ[j].pc + (v1 % IDX_MOD));
	else
		sum = v1;
	sum += v2;
	sum = read_bytes(env, env->champ[j].pc + (sum % IDX_MOD));
	env->champ[j].r[reg] = sum;
	ft_printf("in reg = %#.8x\n", env->champ[j].r[reg]);
}

void		op_lldi(t_env *env, int j)
{
	int	v1;
	int	v2;
	int	v3;
	int	sum;
	int	cursor;

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	v3 = get_value_index(env, j, &cursor, 3);
	sum = read_multi_bytes(env->memory,
				env->champ[j].pc + v1 + v2 + 4, REG_SIZE);
	env->champ[j].r[v3] = sum;

}
