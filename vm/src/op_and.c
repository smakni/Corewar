/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:38:43 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 16:47:18 by smakni           ###   ########.fr       */
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

	env->champ[j].op.name = "and";
	cursor = 1;
	nb_reg1 = 1;
	nb_reg2 = 1;
	if (type_param(env->memory[env->champ[j].pc + 1], 1) == REG_CODE)
	{
		nb_reg1 = env->memory[env->champ[j].pc + cursor + 1];
		diff = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
			diff = get_value(env, j, &cursor, 1);
		else
			cursor++;
	}
	else
		diff = get_value(env, j, &cursor, 1);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == REG_CODE)
	{
		nb_reg2 = env->memory[env->champ[j].pc + cursor + 1];
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
	nb_reg3 = env->memory[env->champ[j].pc + cursor];
	if (diff == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
			&& nb_reg2 >= 1 && nb_reg2 <= 16
			&& nb_reg3 >= 1 && nb_reg3 <= 16)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
		env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
	env->champ[j].pc += 1 + cursor;
}
