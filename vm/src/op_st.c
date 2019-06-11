/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:20:45 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 17:29:56 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
/*
static int	read_two_bytes(t_env *env, int current_pos, int *cursor)
{
	short	ret;

	ret = env->memory[current_pos + *cursor] << 8;
	ret += env->memory[current_pos + *cursor + 1];
	(*cursor) += 2;
	return (ret);
}
*/
void		op_st(t_env *env, unsigned int j)
{
	int		cursor;
	short	dest;
	int		reg_content;
	int		current_pos;
	int		nb_reg;

	current_pos = env->champ[j].pc;
	cursor = 1;
	if (check_args(env, j, &cursor, 2))
	{
		env->champ[j].op.name = "st";
		nb_reg = env->memory[current_pos + 2];
		save_param(env, j, nb_reg, REG_CODE, 0);
		reg_content = get_value(env, j, &cursor, 1);
		cursor++;
		if (type_param(env->memory[current_pos + 1], 2) == IND_CODE)
		{
			dest = read_bytes(env->memory, current_pos + cursor, IND_SIZE) % IDX_MOD;
			cursor += 2;
			save_param(env, j, dest, IND_CODE, 1);
			if (nb_reg >= 1 && nb_reg <= 16)
			{
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
		}
		else
		{
			dest = env->memory[env->champ[j].pc + cursor];
			save_param(env, j, dest, IND_CODE, 1);
			cursor++;
			if (nb_reg >= 1 && nb_reg <= 16)
				env->champ[j].r[dest] = reg_content;
		}
	}
	env->champ[j].pc += cursor;
	if (env->visu == 1)
		update_visu(env, dest, j);
}
