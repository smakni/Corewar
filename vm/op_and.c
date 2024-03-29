/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:38:43 by cmoulini          #+#    #+#             */
/*   Updated: 2019/07/30 11:23:08 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	and_first_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v1 = get_value(env, j, &data->cursor, 1);
		else
			data->cursor++;
	}
	else
		data->v1 = get_value(env, j, &data->cursor, 1);
}

static void	and_second_param(t_env *env, unsigned int j, t_op_vars *data,
				int *nb_reg)
{
	if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
	{
		*nb_reg = env->process[j].op.saved[data->cursor + 1];
		if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
			data->v2 = get_value(env, j, &data->cursor, 2);
		else
			data->cursor++;
	}
	else
		data->v2 = get_value(env, j, &data->cursor, 2);
}

static void	and_third_param(t_env *env, unsigned int j, t_op_vars *data,
				int nb_reg[3])
{
	if (all_reg_valid(nb_reg, 3))
	{
		set_carry(env, j, data->v1);
		env->process[j].op.name = "and";
		env->process[j].r[env->process[j].op.saved[data->cursor]] = data->v1;
	}
}

void		op_and(t_env *env, unsigned int j)
{
	t_op_vars	data;
	int			nb_reg[3];

	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 1;
		nb_reg[1] = 1;
		and_first_param(env, j, &data, &nb_reg[0]);
		and_second_param(env, j, &data, &nb_reg[1]);
		if (nb_reg[0] >= 1 && nb_reg[0] <= REG_NUMBER
				&& nb_reg[1] >= 1 && nb_reg[1] <= REG_NUMBER)
			data.v1 &= data.v2;
		data.cursor++;
		nb_reg[2] = env->process[j].op.saved[data.cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		and_third_param(env, j, &data, nb_reg);
		data.cursor++;
	}
	else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	env->process[j].pc += data.cursor;
}
