/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/05 23:36:57 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_ld(t_env *env, unsigned int j)
{
	int		cursor;
	int		nb_reg;
	int	value;
	int		current_pos;

	env->champ[j].op.name = "ld";
	env->champ[j].op.nb_params = 2;
	current_pos = env->champ[j].pc;
	cursor = 1;
	value = get_value(env, j, &cursor, 1);
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
