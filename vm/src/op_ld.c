/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/11 21:45:33 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ld(t_env *env, unsigned int j)
{
	int	cursor;
	int	nb_reg;
	int	value;
	int	current_pos;

	current_pos = env->champ[j].pc;
	cursor = 1;
	if (check_args(env, j, &cursor, 2))
	{
		env->champ[j].op.name = "ld";
		value = get_value(env, j, &cursor, 1);
		save_param(env, j, value, IND_CODE, 0);
		cursor++;
		nb_reg = env->memory[(current_pos + cursor) % MEM_SIZE];
		save_param(env, j, nb_reg, REG_CODE, 1);
		cursor++;
		if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
			env->champ[j].carry = 1;
		else
			env->champ[j].carry = 0;
		if (nb_reg >= 1 && nb_reg <= 16)
			env->champ[j].r[nb_reg] = value;
	}
	else
		cursor += decode_byte_param(env->memory[env->champ[j].pc + 1], 0, 2);
	env->champ[j].pc += cursor;
}
