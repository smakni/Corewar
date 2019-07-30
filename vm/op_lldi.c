/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:21:50 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/30 11:24:02 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	lldi_first_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v1 = get_value_index(env, j, &data->cursor, 1);
		else
			data->cursor++;
	}
	else
		data->v1 = get_value_index(env, j, &data->cursor, 1);
}

static void	lldi_second_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v2 = get_value_index(env, j, &data->cursor, 2);
		else
			data->cursor++;
	}
	else
		data->v2 = get_value_index(env, j, &data->cursor, 2);
}

static void	lldi_third_param(t_env *env, unsigned int j, t_op_vars *data,
				int nb_reg[3])
{
	if (all_reg_valid(nb_reg, 3))
	{
		env->process[j].op.name = "lldi";
		data->v3 = data->v1 + data->v2;
		data->v3 = (env->process[j].pc + data->v3) % MEM_SIZE;
		if (data->v3 < 0)
			data->v3 += MEM_SIZE;
		data->v3 = read_bytes(env->memory, data->v3, REG_SIZE);
		env->process[j].r[nb_reg[2]] = data->v3;
		set_carry(env, j, data->v3);
	}
}

void		op_lldi(t_env *env, unsigned int j)
{
	t_op_vars	data;
	int			nb_reg[3];

	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 1;
		nb_reg[1] = 1;
		lldi_first_param(env, j, &data, &nb_reg[0]);
		lldi_second_param(env, j, &data, &nb_reg[1]);
		data.cursor++;
		nb_reg[2] = env->process[j].op.saved[data.cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		data.cursor++;
		lldi_third_param(env, j, &data, nb_reg);
	}
	else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += data.cursor;
}
