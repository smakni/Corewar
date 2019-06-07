/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/07 13:56:51 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr_no_limit(t_env *env, unsigned int j, int *cursor)
{
	int	value;
	int	ret;

	(*cursor)++;
	value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
	//save_param(env, j, value, IND_CODE);
	ret = read_bytes(env->memory, env->champ[j].pc + value, REG_SIZE);
	*cursor += IND_SIZE - 1;
	return (ret);
}

void		op_lld(t_env *env, unsigned int j)
{
	int		cursor;
	int		nb_reg;
	int	value;
	int		current_pos;

	env->champ[j].op.name = "lld";
	current_pos = env->champ[j].pc;
	cursor = 1;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
	{
		value = get_value(env, j, &cursor, 1);
		//save_param(env, j, value, DIR_CODE);
	}
	else
		value = get_addr_no_limit(env, j, &cursor);
	cursor++;
	nb_reg = env->memory[current_pos + cursor];
	//save_param(env, j, nb_reg, REG_CODE);
	cursor++;
	if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	if (nb_reg >= 1 && nb_reg <= 16)
		env->champ[j].r[nb_reg] = value;
	env->champ[j].pc += cursor;
}
