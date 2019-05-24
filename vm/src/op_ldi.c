/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:24:07 by smakni            #+#    #+#             */
/*   Updated: 2019/05/24 21:17:34 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ldi(t_env *env, unsigned j)
{
	int	v1;
	int	v2;
	int	reg;
	int sum;
	int	cursor;

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	//ft_printf("cursor = %i\n", env->champ[j].pc + cursor);
	cursor++;
	reg = env->memory[env->champ[j].pc + cursor];
	//ft_printf("v1, v2, reg = %i, %x, %i\n", v1, v2, reg);
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == IND_CODE)
		sum = read_bytes(env, env->champ[j].pc + (v1 % IDX_MOD));
	else
		sum = v1;
	sum += v2;
	//ft_printf("IND VALUE = %i\nV2 VALUE = %#.8x\n", env->champ[j].pc + (sum % (IDX_MOD)), v2);
	sum = env->champ[j].pc + (sum % (IDX_MOD));
	if (sum < 0)
		sum += MEM_SIZE;
	sum = read_bytes(env, sum);
	env->champ[j].r[reg] = sum;
	//ft_printf("in reg = %#.8x\n", env->champ[j].r[reg]);
	env->champ[j].pc += cursor + 1;
}
