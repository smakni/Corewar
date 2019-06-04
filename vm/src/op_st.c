/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:20:45 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/03 23:31:04 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	read_two_bytes(t_env *env, int current_pos, int *cursor)
{
	short	ret;

	ret = env->memory[current_pos + *cursor] << 8;
	ret += env->memory[current_pos + *cursor + 1];
	(*cursor) += 2;
	return (ret);
}

void op_st(t_env *env, unsigned j)
{
	int		cursor;
	short	dest;
	int		reg_content;
	int		current_pos;

	current_pos = env->champ[j].pc;
	cursor = 1;
	reg_content = get_value(env, j, &cursor, 1);
	cursor++;
	if (type_param(env->memory[current_pos + 1], 2) == IND_CODE)
	{
		dest = read_two_bytes(env, current_pos, &cursor) % IDX_MOD;
		dest += current_pos;
		if (dest < 0)
			dest += MEM_SIZE;
		else if (dest >= MEM_SIZE)
			dest %= MEM_SIZE;
		env->memory[dest % MEM_SIZE] = reg_content >> 24;
		env->memory[(dest + 1) % MEM_SIZE] = reg_content >> 16;
		env->memory[(dest + 2) % MEM_SIZE] = reg_content >> 8;
		env->memory[(dest + 3) % MEM_SIZE] = reg_content;
	}
	else
	{
		dest = env->memory[env->champ[j].pc + cursor];
		cursor++;
		env->champ[j].r[dest] = reg_content;
	}
	env->champ[j].pc += cursor;
	if (env->visu == 1)
		update_visu(env, dest, j);
}
