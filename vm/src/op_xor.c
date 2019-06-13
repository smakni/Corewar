/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:17:31 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/13 17:41:02 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_xor(t_env *env, unsigned int j)
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
		env->champ[j].op.name = "xor";
		nb_reg1 = 1;
		nb_reg2 = 1;
		if (type_param(env->champ[j].op.saved[1], 1) == REG_CODE)
		{
			nb_reg1 = env->champ[j].op.saved[cursor + 1];
			save_param(env, j, nb_reg1, REG_CODE, 0);
			diff = 0;
			if (nb_reg1 >= 1 && nb_reg1 <= 16)
				diff = get_value(env, j, &cursor, 1);
			else
				cursor++;
		}
		else
		{
			diff = get_value(env, j, &cursor, 1);
			save_param(env, j, diff, DIR_CODE, 0);
		}
		if (type_param(env->champ[j].op.saved[1], 2) == REG_CODE)
		{
			nb_reg2 = env->champ[j].op.saved[cursor + 1];
			save_param(env, j, nb_reg2, REG_CODE, 1);
			value = 0;
			if (nb_reg2 >= 1 && nb_reg2 <= 16)
				value = get_value(env, j, &cursor, 2);
			else
				cursor++;
		}
		else
		{
			value = get_value(env, j, &cursor, 2);
			save_param(env, j, value, DIR_CODE, 1);
		}
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16)
			diff ^= value;
		cursor++;
		nb_reg3 = env->champ[j].op.saved[cursor];
		save_param(env, j, nb_reg3, REG_CODE, 2);
		if (diff == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
				&& nb_reg2 >= 1 && nb_reg2 <= 16
				&& nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].carry = 1;
		else
			env->champ[j].carry = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].r[env->champ[j].op.saved[cursor]] = diff;
		cursor++;
	}
	else
		cursor += decode_byte_param(env->champ[j].op.saved[1], 0, 3);
	env->champ[j].pc += cursor;
}
