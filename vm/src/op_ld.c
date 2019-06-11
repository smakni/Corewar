/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/11 15:02:44 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ld(t_env *env, unsigned int j)
{
	int	cursor;
	int	nb_reg;
	int	value;
	int	current_pos;

	env->champ[j].op.name = "ld";
	current_pos = env->champ[j].pc;
	cursor = 1;
	if (check_args(env, j, &cursor, 2))
	{
		value = get_value(env, j, &cursor, 1);
		save_param(env, j, value, IND_CODE, 0);
		cursor++;
		nb_reg = env->memory[current_pos + cursor];
		save_param(env, j, nb_reg, REG_CODE, 1);
		cursor++;
		if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
			env->champ[j].carry = 1;
		else
			env->champ[j].carry = 0;
		if (nb_reg >= 1 && nb_reg <= 16)
			env->champ[j].r[nb_reg] = value;
	}
	env->champ[j].pc += cursor;
}
