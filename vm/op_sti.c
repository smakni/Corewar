/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 00:00:36 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/30 11:14:49 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	sti_second_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 2) == IND_CODE)
	{
		data->v2 = read_bytes(env->memory, data->v3 + data->cursor, IND_SIZE);
		data->v2 += data->v3;
		data->cursor += 2;
		if (data->v2 < 0)
			data->v2 += MEM_SIZE;
		else if (data->v2 >= MEM_SIZE)
			data->v2 %= MEM_SIZE;
		data->dest = read_bytes(env->memory, data->v2, 4);
		if (env->verb == 1)
			save_ind_param(env, j, read_bytes(env->memory, data->v2, 4), 1);
	}
	else if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
		data->dest = get_reg_content_arg2(env, j, &data->cursor, nb_reg);
	else
	{
		data->dest = read_bytes(env->process[j].op.saved,
						data->cursor, IND_SIZE);
		data->cursor += 2;
		if (env->verb == 1)
			save_ind_param(env, j, data->dest, 1);
	}
}

static void	sti_third_param(t_env *env, unsigned int j,
				t_op_vars *data, int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 3) == REG_CODE)
		data->dest += get_reg_content_arg3(env, j, &data->cursor, nb_reg);
	else
	{
		data->v2 = read_bytes(env->process[j].op.saved, data->cursor, 2);
		data->cursor += 2;
		data->dest += data->v2;
		if (env->verb == 1)
			save_ind_param(env, j, data->v2, 2);
	}
}

static void	sti_op(t_env *env, unsigned int j, t_op_vars *data, int nb_reg[3])
{
	if (all_reg_valid(nb_reg, 3))
	{
		env->process[j].op.name = "sti";
		data->dest %= IDX_MOD;
		data->dest += data->v3;
		if (data->dest < 0)
			data->dest += MEM_SIZE;
		env->memory[data->dest % MEM_SIZE] = data->v1 >> 24;
		env->memory[(data->dest + 1) % MEM_SIZE] = data->v1 >> 16;
		env->memory[(data->dest + 2) % MEM_SIZE] = data->v1 >> 8;
		env->memory[(data->dest + 3) % MEM_SIZE] = data->v1;
		if (env->option == 1 || env->option == 2)
			update_visu(env, data->dest, j);
	}
}

void		op_sti(t_env *env, unsigned int j)
{
	t_op_vars	data;
	int			nb_reg[3];

	ft_bzero(&data, sizeof(t_op_vars));
	data.v3 = env->process[j].pc;
	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 0;
		data.cursor++;
		data.v1 = get_reg_content_arg1(env, j, &data.cursor, &nb_reg[0]);
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[0], 0);
		nb_reg[1] = 1;
		nb_reg[2] = 1;
		sti_second_param(env, j, &data, &nb_reg[1]);
		sti_third_param(env, j, &data, &nb_reg[2]);
		sti_op(env, j, &data, nb_reg);
	}
	else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += data.cursor;
}
