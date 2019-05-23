/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:17:31 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/23 19:23:21 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_xor(t_env *env, int j)
{
	int cursor;
	int	value;
	int	diff;

	cursor = 1;
	diff = get_value(env, j, &cursor, 1);
	value = get_value(env, j, &cursor, 2);
	diff ^= value;
	cursor++;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
	env->champ[j].pc += 1 + cursor;
	env->champ[j].carry = 1;
}
