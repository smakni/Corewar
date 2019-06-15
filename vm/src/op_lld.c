/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/14 17:52:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr_no_limit(t_env *env, unsigned int j, int *cursor)
{
	int	value;
	int	ret;

	(*cursor)++;
	value = read_bytes(env->memory, env->proc[j].pc + *cursor, IND_SIZE);
	ret = read_bytes(env->memory, env->proc[j].pc + value, REG_SIZE);
	save_param(env, j, ret, IND_CODE, 0);
	*cursor += IND_SIZE - 1;
	return (ret);
}

void		op_lld(t_env *env, unsigned int j)
{
	int		cursor;
	int		nb_reg;
	int	value;

	cursor = 1;
	if (check_args(env, j, &cursor, 2))
	{
		env->proc[j].op.name = "lld";
		if (type_param(env->proc[j].op.saved[1], 1) == DIR_CODE)
		{
			value = get_value(env, j, &cursor, 1);
			save_param(env, j, value, DIR_CODE, 0);
		}
		else
			value = get_addr_no_limit(env, j, &cursor);
		cursor++;
		nb_reg = env->proc[j].op.saved[cursor];
		save_param(env, j, nb_reg, REG_CODE, 1);
		cursor++;
		if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
			env->proc[j].carry = 1;
		else
			env->proc[j].carry = 0;
		if (nb_reg >= 1 && nb_reg <= 16)
			env->proc[j].r[nb_reg] = value;
	}
	else
		cursor += decode_byte_param(env->proc[j].op.saved[1], 0, 2);
	env->proc[j].pc += cursor;
}
