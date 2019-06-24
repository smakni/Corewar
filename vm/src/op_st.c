/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:20:45 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/21 17:41:40 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_st(t_env *env, unsigned int j)
{
	int		cursor;
	short	dest;
	int		reg_content;
	int		current_pos;
	int		nb_reg;

	current_pos = env->process[j].pc;
	cursor = 1;
	dest = 0;
	if (check_args(env, j, &cursor, 2))
	{
		env->process[j].op.name = "st";
		nb_reg = env->process[j].op.saved[2];
		save_param(env, j, nb_reg, REG_CODE, 0);
		reg_content = get_value(env, j, &cursor, 1);
		cursor++;
		if (type_param(env->process[j].op.saved[1], 2) == IND_CODE)
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
			dest = env->process[j].op.saved[cursor];
			save_param(env, j, dest, IND_CODE, 1);
			cursor++;
			if (nb_reg >= 1 && nb_reg <= 16)
				env->process[j].r[dest] = reg_content;
		}
		if (env->option == 1 || env->option == 2)
			update_visu(env, dest, j);
	}
	else if (cursor == 1)
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 2);
	env->process[j].pc += cursor;
}
