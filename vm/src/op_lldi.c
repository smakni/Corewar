/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:21:50 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/24 21:17:41 by sabri            ###   ########.fr       */
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

	cursor = 1;
	v1 = get_value_index(env, j, &cursor, 1);
	v2 = get_value_index(env, j, &cursor, 2);
	cursor++;
	reg = env->memory[env->champ[j].pc + cursor];
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == IND_CODE)
		sum = read_bytes(env, env->champ[j].pc + (v1 % MEM_SIZE));
	else
		sum = v1;
	sum = env->champ[j].pc + ((sum + v2) % MEM_SIZE);
	if (sum < 0)
		sum += MEM_SIZE;
	sum = read_bytes(env, sum);
	if (sum == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[reg] = sum;
	env->champ[j].pc += cursor + 1;
}
