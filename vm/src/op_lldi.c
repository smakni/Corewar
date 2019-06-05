/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:21:50 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/05 15:08:40 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_lldi(t_env *env, unsigned j)
{
	int	v1;
	int	v2;
	int	reg;
	int sum;
	int	cursor;

	env->champ[j].op.name = "lldi";
	env->champ[j].op.nb_params = 2;
	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	cursor++;
	reg = env->memory[env->champ[j].pc + cursor];
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == IND_CODE)
		sum = read_bytes(env->memory, env->champ[j].pc + (v1 % MEM_SIZE), 4);
	else
		sum = v1;
	sum = env->champ[j].pc + ((sum + v2) % MEM_SIZE);
	if (sum < 0)
		sum += MEM_SIZE;
	sum = read_bytes(env->memory, sum, 4);
	if (sum == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[reg] = sum;
	env->champ[j].pc += cursor + 1;
}
