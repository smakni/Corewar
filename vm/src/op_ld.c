/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/21 17:41:40 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ld(t_env *env, unsigned int j)
{
	int	cursor;
	int	nb_reg;
	int	value;

	cursor = 1;
	if (check_args(env, j, &cursor, 2))
	{
		value = get_value(env, j, &cursor, 1);
		save_param(env, j, value, IND_CODE, 0);
		cursor++;
		nb_reg = env->process[j].op.saved[cursor];
		save_param(env, j, nb_reg, REG_CODE, 1);
		cursor++;
		if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
			env->process[j].carry = 1;
		else
			env->process[j].carry = 0;
		if (nb_reg >= 1 && nb_reg <= 16)
		{	
			env->process[j].op.name = "ld";
			env->process[j].r[nb_reg] = value;
		}
	}
	else if (cursor == 1)
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 2);
	env->process[j].pc += cursor;
}
