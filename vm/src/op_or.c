/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:17:24 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/04 12:55:00 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	or_first_param(t_env *env, unsigned int j, t_op_vars *data,
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

static void	or_second_param(t_env *env, unsigned int j, t_op_vars *data,
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

static void	or_third_param(t_env *env, unsigned int j, t_op_vars *data,
				int nb_reg[3])
{
	if (nb_reg[0] >= 1 && nb_reg[0] <= REG_NUMBER
			&& nb_reg[1] >= 1 && nb_reg[1] <= REG_NUMBER
			&& nb_reg[2] >= 1 && nb_reg[2] <= REG_NUMBER)
	{
		env->process[j].carry = (data->v1 == 0) ? 1 : 0;
		env->process[j].op.name = "or";
		env->process[j].r[env->process[j].op.saved[data->cursor]] = data->v1;
	}
}

void		op_or(t_env *env, unsigned int j)
{
	t_op_vars	data;
	int			nb_reg[3];

	data.cursor = 1;
	if (check_args(env, j, data.cursor, 3))
	{
		nb_reg[0] = 1;
		nb_reg[1] = 1;
		or_first_param(env, j, &data, &nb_reg[0]);
		or_second_param(env, j, &data, &nb_reg[1]);
		if (nb_reg[0] >= 1 && nb_reg[0] <= REG_NUMBER
				&& nb_reg[1] >= 1 && nb_reg[1] <= REG_NUMBER)
			data.v1 |= data.v2;
		data.cursor++;
		nb_reg[2] = env->process[j].op.saved[data.cursor];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		or_third_param(env, j, &data, nb_reg);
		data.cursor++;
	}
	else
		data.cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	env->process[j].pc += data.cursor;
}
