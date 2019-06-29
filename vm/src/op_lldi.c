/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:21:50 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/29 17:12:16 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_lldi(t_env *env, unsigned int j)
{
	t_op_vars data;
	int	nb_reg[3];

	ft_bzero(&data, sizeof(t_op_vars));
	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 1;
		nb_reg[1] = 1;
		if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
		{
			nb_reg[0] = env->process[j].op.saved[data.cursor + 1];
			if (nb_reg[0] >= 1 && nb_reg[0] <= 16)
				data.v1 = get_value_index(env, j, &data.cursor, 1);
			else
				data.cursor++;
		}
		else
		{
			data.v1 = get_value_index(env, j, &data.cursor, 1);
		}
		if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
		{
			nb_reg[1] = env->process[j].op.saved[data.cursor + 1];
			if (nb_reg[1] >= 1 && nb_reg[1] <= 16)
				data.v2 = get_value_index(env, j, &data.cursor, 2);
			else
				data.cursor++;
		}
		else
			data.v2 = get_value_index(env, j, &data.cursor, 2);
		data.cursor++;
		nb_reg[2] = env->process[j].op.saved[data.cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		data.cursor++;
		if (nb_reg[0] >= 1 && nb_reg[0] <= 16 && nb_reg[1] >= 1 && nb_reg[1] <= 16 && nb_reg[2] >= 1 && nb_reg[2] <= 16)
		{
			env->process[j].op.name = "lldi";
			if (type_param(env->process[j].op.saved[1], 1) == IND_CODE)
				data.v3 = read_bytes(env->memory, env->process[j].pc + data.v1, REG_SIZE);
			else
				data.v3 = data.v1;
			data.v3 += data.v2;
			data.v3 = (env->process[j].pc + data.v3) % MEM_SIZE;
			if (data.v3 < 0)
				data.v3 += MEM_SIZE;
			data.v3 = read_bytes(env->memory, data.v3, REG_SIZE);
			env->process[j].r[nb_reg[2]] = data.v3;
			env->process[j].carry = (data.v3 == 0) ? 1 : 0;
		}
	}
else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += data.cursor;
}
