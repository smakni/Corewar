/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:24:07 by smakni            #+#    #+#             */
/*   Updated: 2019/06/05 22:06:37 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ldi(t_env *env, unsigned j)
{
	int	v1;
	int	v2;
	int sum;
	int	cursor;
	int	nb_reg1;
	int	nb_reg2;
	int	nb_reg3;

	env->champ[j].op.name = "ldi";
	env->champ[j].op.nb_params = 3;
	cursor = 1;
	nb_reg1 = 1;
	nb_reg2 = 1;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == REG_CODE)
	{
		nb_reg1 = env->memory[env->champ[j].pc + cursor + 1];
		v1 = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
			v1 = get_value_index(env, j, &cursor, 1);
		else
			cursor++;
	}
	else
		v1 = get_value_index(env, j, &cursor, 1);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == REG_CODE)
	{
		nb_reg2 = env->memory[env->champ[j].pc + cursor + 1];
		v2 = 0;
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
			v2 = get_value_index(env, j, &cursor, 2);
		else
			cursor++;
	}
	else
		v2 = get_value_index(env, j, &cursor, 2);
	cursor++;
	nb_reg3 = env->memory[env->champ[j].pc + cursor];
	if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
	{
		if (type_param(env->memory[env->champ[j].pc + 1], 1) == IND_CODE)
			sum = read_bytes(env->memory, env->champ[j].pc + (v1 % IDX_MOD), REG_SIZE);
		else
			sum = v1;
		sum += v2;
		sum = (env->champ[j].pc + (sum % (IDX_MOD))) % MEM_SIZE;
		if (sum < 0)
			sum += MEM_SIZE;
		sum = read_bytes(env->memory, sum, REG_SIZE);
		env->champ[j].r[nb_reg3] = sum;
	}
	env->champ[j].pc += cursor + 1;
}
