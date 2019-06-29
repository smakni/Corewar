/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:20:45 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/29 12:56:42 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	type_ind(t_env *env, unsigned int j, int *cursor, int nb_reg)
{
	int		current_pos;
	int		reg_content;
	short	dest;

	current_pos = env->process[j].pc;
	reg_content = get_value(env, j, cursor, 1);
	(*cursor)++;
	dest = read_bytes(env->memory, current_pos + *cursor, IND_SIZE);
	if (env->verb == 1)
		save_ind_param(env, j, dest, 1);
	dest %= IDX_MOD;
	*cursor += 2;
	if (nb_reg >= 1 && nb_reg <= REG_NUMBER)
	{
		env->process[j].op.name = "st";
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

static void	type_reg(t_env *env, unsigned int j, int *cursor, int nb_reg)
{
	int		reg_content;
	short	dest;

	reg_content = get_value(env, j, cursor, 1);
	(*cursor)++;
	dest = env->process[j].op.saved[*cursor];
	if (env->verb == 1)
		save_ind_param(env, j, dest, 1);
	(*cursor)++;
	if (nb_reg >= 1 && nb_reg <= REG_NUMBER)
	{
		env->process[j].op.name = "st";
		env->process[j].r[dest] = reg_content;
	}
	if (env->option == 1 || env->option == 2)
		update_visu(env, dest, j);
}

void		op_st(t_env *env, unsigned int j)
{
	int		cursor;
	// short	dest;
	// int		reg_content;
	// int		current_pos;
	int		nb_reg;

	// current_pos = env->process[j].pc;
	cursor = 1;
	// dest = 0;
	if (check_args(env, j, &cursor, 2))
	{
		nb_reg = env->process[j].op.saved[2];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg, 0);
		// reg_content = get_value(env, j, &cursor, 1);
		// cursor++;
		if (type_param(env->process[j].op.saved[1], 2) == IND_CODE)
		{
			type_ind(env, j, &cursor, nb_reg);
			// dest = read_bytes(env->memory, current_pos + cursor, IND_SIZE);
			// if (env->verb == 1)
			// 	save_ind_param(env, j, dest, 1);
			// dest %= IDX_MOD;
			// cursor += 2;
			// if (nb_reg >= 1 && nb_reg <= 16)
			// {
			// 	env->process[j].op.name = "st";
			// 	dest += current_pos;
			// 	if (dest < 0)
			// 		dest += MEM_SIZE;
			// 	else if (dest >= MEM_SIZE)
			// 		dest %= MEM_SIZE;
			// 	env->memory[dest % MEM_SIZE] = reg_content >> 24;
			// 	env->memory[(dest + 1) % MEM_SIZE] = reg_content >> 16;
			// 	env->memory[(dest + 2) % MEM_SIZE] = reg_content >> 8;
			// 	env->memory[(dest + 3) % MEM_SIZE] = reg_content;
			// }
		}
		else
		{
			type_reg(env, j, &cursor, nb_reg);
			// dest = env->process[j].op.saved[cursor];
			// if (env->verb == 1)
			// 	save_ind_param(env, j, dest, 1);
			// cursor++;
			// if (nb_reg >= 1 && nb_reg <= 16)
			// {
			// 	env->process[j].op.name = "st";
			// 	env->process[j].r[dest] = reg_content;
			// }
		}
		// if (env->option == 1 || env->option == 2)
		// 	update_visu(env, dest, j);
	}
	else
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 2);
	env->process[j].pc += cursor;
}
