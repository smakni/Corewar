/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:38:43 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/25 20:29:13 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_and(t_env *env, unsigned int j)
{
	int cursor;
	int	value;
	int	diff;
	int	nb_reg1;
	int	nb_reg2;
	int	nb_reg3;

	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		nb_reg1 = 1;
		nb_reg2 = 1;
		if (type_param(env->process[j].op.saved[1], 1) == REG_CODE)
		{
			nb_reg1 = env->process[j].op.saved[cursor + 1];
			save_param(env, j, nb_reg1, REG_CODE, 0);
			diff = 0;
			if (nb_reg1 >= 1 && nb_reg1 <= 16)
				diff = get_value(env, j, &cursor, 1);
			else
				cursor++;
		}
		else
			diff = get_value(env, j, &cursor, 1);
		if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
		{
			nb_reg2 = env->process[j].op.saved[cursor + 1];
			save_param(env, j, nb_reg2, REG_CODE, 1);
			value = 0;
			if (nb_reg2 >= 1 && nb_reg2 <= 16)
				value = get_value(env, j, &cursor, 2);
			else
				cursor++;
		}
		else
			value = get_value(env, j, &cursor, 2);
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16)
			diff &= value;
		cursor++;
		nb_reg3 = env->process[j].op.saved[cursor];
		save_param(env, j, nb_reg3, REG_CODE, 2);
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
		{
			if (diff == 0)
				env->process[j].carry = 1;
			else
				env->process[j].carry = 0;
			env->process[j].op.name = "and";
			env->process[j].r[env->process[j].op.saved[cursor]] = diff;
		}
		cursor++;
	}
	else
	{
		if (env->process[j].op.code != env->process[j].op.saved[0])
			cursor++;
		else
			cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	}
	env->process[j].pc += cursor;
}
