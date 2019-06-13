/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/06/13 17:42:14 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	exec_op(t_env *env, unsigned j)
{
	void	(*op_fun[16])(t_env*, unsigned);
	int		index;
	int		save;
	int		x;
	int		y;

	save = env->champ[j].pc;
	if (env->visu == 1 && env->champ[j].live != -1)
	{
		x = env->champ[j].live % 64 * 3;
		y = env->champ[j].live / 64;
		mvwchgat(env->mem, y, x, 2, A_NORMAL, env->champ[j].color, NULL);
	}
	op_fun[0] = op_live;
	op_fun[1] = op_ld;
	op_fun[2] = op_st;
	op_fun[3] = op_add;
	op_fun[4] = op_sub;
	op_fun[5] = op_and;
	op_fun[6] = op_or;
	op_fun[7] = op_xor;
	op_fun[8] = op_zjmp;
	op_fun[9] = op_ldi;
	op_fun[10] = op_sti;
	op_fun[11] = op_fork;
	op_fun[12] = op_lld;
	op_fun[13] = op_lldi;
	op_fun[14] = op_lfork;
	op_fun[15] = op_aff;
	index = env->champ[j].op.saved[0];
	if (env->visu == 1)
		remove_bold(env, j);
	if (index >= 0x01 && index <= 0x10)
	{
		op_fun[index - 1](env, j);
		if (env->visu == 0)
			aff_operations(env, j, save);
	}
	else
	{
		env->champ[j].pc++;
	}
	if (env->visu == 1)
		redraw_pc_2(env, env->champ[j].pc, env->champ[j].pc - save);
}
