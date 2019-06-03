/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:40:47 by sabri             #+#    #+#             */
/*   Updated: 2019/05/31 18:53:41 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_sti(t_env *env, unsigned j)
{
	unsigned	reg_content;
	int			cursor;
	int			v1;
	int			dest;

	dest = env->champ[j].pc;
	cursor = 1;
	reg_content = (unsigned)get_value_index(env, j, &cursor, 1);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == IND_CODE)
	{
		v1 = get_value_index(env, j, &cursor, 2);
		dest += read_bytes(env->memory, env->champ[j].pc + (v1 % IDX_MOD), 4);
	}
	else
		dest += get_value_index(env, j, &cursor, 2);
	dest += get_value_index(env, j, &cursor, 3);
	dest %= IDX_MOD;
//	ft_printf("%i\n", dest);
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
	env->champ[j].pc += 1 + cursor;
	if (env->visu == 1)
		update_visu(env, dest, j);
}
