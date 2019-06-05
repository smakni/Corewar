/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:40:47 by sabri             #+#    #+#             */
/*   Updated: 2019/06/05 15:09:23 by smakni           ###   ########.fr       */
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

static int	get_reg_content(t_env *env, unsigned int j, int *cursor)
{
	int	content;

	content = env->champ[j].r[env->memory[env->champ[j].pc + *cursor]];
	(*cursor)++;
	return (content);
}

void	op_sti(t_env *env, unsigned int j)
{
	int		cursor;
	short	dest;
	int		reg_content;
	int		current_pos;
	int		tmp;

	env->champ[j].op.name = "sti";
	env->champ[j].op.nb_params = 3;
	current_pos = env->champ[j].pc;
	cursor = 2;
	reg_content = get_reg_content(env, j, &cursor);
	if (type_param(env->memory[current_pos + 1], 2) == IND_CODE)
	{
		tmp = read_two_bytes(env, current_pos, &cursor) % IDX_MOD;
		if (current_pos + tmp < 0)
			tmp += (current_pos + MEM_SIZE);
		else if (current_pos + tmp >= MEM_SIZE)
			tmp = (current_pos + tmp) % MEM_SIZE;
		dest = read_bytes(env->memory, tmp, 4);
	}
	else if (type_param(env->memory[current_pos + 1], 2) == REG_CODE)
		dest = get_reg_content(env, j, &cursor);
	else
		dest = read_two_bytes(env, current_pos, &cursor) % IDX_MOD;
	if (type_param(env->memory[current_pos + 1], 3) == REG_CODE)
		dest += get_reg_content(env, j, &cursor);
	else
		dest += read_two_bytes(env, current_pos, &cursor) % IDX_MOD;
	dest += current_pos;
	if (dest < 0)
		dest += MEM_SIZE;
	else if (dest >= MEM_SIZE)
		dest %= MEM_SIZE;
	env->memory[dest % MEM_SIZE] = reg_content >> 24;
	env->memory[(dest + 1) % MEM_SIZE] = reg_content >> 16;
	env->memory[(dest + 2) % MEM_SIZE] = reg_content >> 8;
	env->memory[(dest + 3) % MEM_SIZE] = reg_content;
	env->champ[j].pc += cursor;
	if (env->visu == 1)
		update_visu(env, dest, j);
}
