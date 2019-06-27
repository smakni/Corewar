/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 00:00:36 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/27 10:48:10 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_reg_content(t_env *env, unsigned int j, int *cursor, int *nb_reg, int param)
{
	int	content;

	content = 0;
	*nb_reg = env->process[j].op.saved[*cursor];
	if (*nb_reg >= 1 && *nb_reg <= 16)
		content = env->process[j].r[*nb_reg];
	if (*cursor > 2)
		if (env->verb == 1)
			save_param(env, j, content, IND_CODE, param);
	(*cursor)++;
	return (content);
}

void	op_sti(t_env *env, unsigned int j)
{
	int		cursor;
	int		dest;
	int		reg_content;
	int		current_pos;
	int		tmp;
	int		nb_reg1;
	int		nb_reg2;
	int		nb_reg3;

	current_pos = env->process[j].pc;
	cursor = 1;
	dest = 0;
	if (check_args(env, j, &cursor, 3))
	{
		nb_reg1 = 0;
		cursor++;
		reg_content = get_reg_content(env, j, &cursor, &nb_reg1, 0);
		if (env->verb == 1)
			save_param(env, j, nb_reg1, REG_CODE, 0);
		nb_reg2 = 1;
		nb_reg3 = 1;
		if (type_param(env->process[j].op.saved[1], 2) == IND_CODE)
		{
			tmp = read_bytes(env->memory, current_pos + cursor, IND_SIZE) % IDX_MOD;
			cursor += 2;
			if (current_pos + tmp < 0)
				tmp += (current_pos + MEM_SIZE);
			else if (current_pos + tmp >= MEM_SIZE)
				tmp = (current_pos + tmp) % MEM_SIZE;
			dest = read_bytes(env->memory, current_pos + tmp, 4) % IDX_MOD;
			if (env->verb == 1)
				save_param(env, j, dest, IND_CODE, 1);
		}
		else if (type_param(env->process[j].op.saved[1], 2) == REG_CODE)
			dest = get_reg_content(env, j, &cursor, &nb_reg2, 1);
		else
		{
			dest = read_bytes(env->process[j].op.saved, cursor, IND_SIZE) % IDX_MOD;
			cursor += 2;
			if (env->verb == 1)
				save_param(env, j, dest, IND_CODE, 1);
		}
		if (type_param(env->process[j].op.saved[1], 3) == REG_CODE)
			dest += get_reg_content(env, j, &cursor, &nb_reg3, 2);
		else
		{
			tmp = read_bytes(env->process[j].op.saved, cursor, 2) % IDX_MOD;
			cursor += 2;
			dest += tmp;
			if (env->verb == 1)
				save_param(env, j, tmp, IND_CODE, 2);
		}
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
		{
			env->process[j].op.name = "sti";
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
		if (env->option == 1 || env->option == 2)
			update_visu(env, dest, j);
	}
else
		cursor += decode_byte_param(env->process[j].op.saved[1], 1, 3);
	env->process[j].pc += cursor;
}
