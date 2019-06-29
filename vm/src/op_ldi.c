/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 12:03:23 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/29 15:26:33 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ldi(t_env *env, unsigned int j)
{
	int	v1;
	int	v2;
	int sum;
	int	cursor;
	int	nb_reg1;
	int	nb_reg2;
	int	nb_reg3;

	cursor = 1;
	if (check_args(env, j, cursor, 3))
	{
		nb_reg1 = 1;
		nb_reg2 = 1;
		if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
		{
			nb_reg1 = env->process[j].op.saved[cursor + 1];
			v1 = 0;
			if (nb_reg1 >= 1 && nb_reg1 <= 16)
				v1 = get_value_index(env, j, &cursor, 1);
			else
				cursor++;
		}
		else
		{
			v1 = get_value_index(env, j, &cursor, 1);
		}
		if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
		{
			nb_reg2 = env->process[j].op.saved[cursor + 1];
			v2 = 0;
			if (nb_reg2 >= 1 && nb_reg2 <= 16)
				v2 = get_value_index(env, j, &cursor, 2);
			else
				cursor++;
		}
		else
		{
			v2 = get_value_index(env, j, &cursor, 2);
		}
		cursor++;
		nb_reg3 = env->process[j].op.saved[cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg3, 2);
		cursor++;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1
				&& nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
		{
			env->process[j].op.name = "ldi";
			if (type_param(env->process[j].op.saved[1], 1) == IND_CODE)
				sum = read_bytes(env->memory, env->process[j].pc + (v1 % IDX_MOD), REG_SIZE);
			else
				sum = v1;
			sum += v2;
			sum = (env->process[j].pc + (sum % (IDX_MOD))) % MEM_SIZE;
			if (sum < 0)
				sum += MEM_SIZE;
			sum = read_bytes(env->memory, sum, REG_SIZE);
			env->process[j].r[nb_reg3] = sum;
		}
	}
	else
		cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += cursor;
}
