/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 12:03:23 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/01 11:52:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	ldi_first_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		data->v1 = 0;
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v1 = (short)get_value_index(env, j, &data->cursor, 1);
		else
			data->cursor++;
	}
	else
	{
		////ft_printf("%i - %i\n", IND_CODE, type_param(env->process[j].op.saved[1], 1));
		data->v1 = get_value_index(env, j, &data->cursor, 1) % IDX_MOD;
	}
}

static void	ldi_second_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		data->v2 = 0;
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v2 = (short)get_value_index(env, j, &data->cursor, 2);
		else
			data->cursor++;
	}
	else
		data->v2 = get_value_index(env, j, &data->cursor, 2);
}

static void	ldi_third_param(t_env *env, unsigned int j, t_op_vars *data,
				int nb_reg[3])
{
	if (nb_reg[0] >= 1 && nb_reg[0] <= REG_NUMBER
			&& nb_reg[1] >= 1 && nb_reg[1] <= REG_NUMBER
			&& nb_reg[2] >= 1 && nb_reg[2] <= REG_NUMBER)
	{
		env->process[j].op.name = "ldi";
		if (type_param(env->process[j].op.saved[1], 1) == IND_CODE)
			data->v3 = read_bytes(env->memory,
				env->process[j].pc + (data->v1 % IDX_MOD), REG_SIZE);
		else
			data->v3 = data->v1;
		data->v3 += data->v2;
		data->v3 = (env->process[j].pc + (data->v3 % (IDX_MOD))) % MEM_SIZE;
		if (data->v3 < 0)
			data->v3 += MEM_SIZE;
		data->v3 = read_bytes(env->memory, data->v3, REG_SIZE);
		env->process[j].r[nb_reg[2]] = data->v3;
		//ft_printf("reg_content = %i\n", env->process[j].r[nb_reg[2]]);
	}
}

void		op_ldi(t_env *env, unsigned int j)
{
	t_op_vars	data;
	int			nb_reg[3];

	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 1;
		nb_reg[1] = 1;
		ldi_first_param(env, j, &data, &nb_reg[0]);
		ldi_second_param(env, j, &data, &nb_reg[1]);
		data.cursor++;
		nb_reg[2] = env->process[j].op.saved[data.cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		data.cursor++;
		ldi_third_param(env, j, &data, nb_reg);
	}
	else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += data.cursor;
}
