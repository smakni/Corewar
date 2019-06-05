/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/06 00:03:26 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr_no_limit(t_env *env, unsigned int j, int *cursor)
{
	int	value;
	int	ret;

	(*cursor)++;
	value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
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
	env->champ[j].op.nb_params = 2;
	current_pos = env->champ[j].pc;
	cursor = 1;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == DIR_CODE)
		value = get_value(env, j, &cursor, 1);
	else
		value = get_addr_no_limit(env, j, &cursor);
	cursor++;
	nb_reg = env->memory[current_pos + cursor];
	cursor++;
	if (value == 0 && nb_reg >= 1 && nb_reg <= 16)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	if (nb_reg >= 1 && nb_reg <= 16)
		env->champ[j].r[nb_reg] = value;
	env->champ[j].pc += cursor;
}
