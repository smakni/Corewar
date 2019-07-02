/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/07/02 19:55:20 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		remove_live_color(t_env *env, unsigned j)
{
	int		x;
	int		y;
	int		color;

	x = env->process[j].live % 64 * 3;
	y = env->process[j].live / 64;
	color = mvwinch(env->mem, y, x) & A_COLOR;
	if (color == COLOR_PAIR(13))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 4, NULL);
	else if (color == COLOR_PAIR(14))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 5, NULL);
	else if (color == COLOR_PAIR(15))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 6, NULL);
	else if (color == COLOR_PAIR(16))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 7, NULL);
}

void			exec_op(t_env *env, unsigned j)
{
	int		index;
	int		save;

	save = env->process[j].pc;
	if ((env->option == 1 || env->option == 2) && env->process[j].live != -1)
		remove_live_color(env, j);
	index = env->process[j].op.code;
	if (env->option == 1 || env->option == 2)
		remove_bold(env, j);
	if (index >= 0x01 && index <= 0x10)
	{
		save_op(env, j);
		env->op_fun[index - 1](env, j);
		if (env->option == 0 && env->verb == 1)
			verbos(env, j, save);
		else if (env->option == 1 && env->verb == 1)
			verbos_visu(env, j, save);
		else if (env->verb == 1 && env->option != 2)
			verbos(env, j, save);
	}
	env->process[j].cycles = 0;
	if (env->option == 1 || env->option == 2)
		redraw_pc(env, env->process[j].pc, env->process[j].pc - save);
}
