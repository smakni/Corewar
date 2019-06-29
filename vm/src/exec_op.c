/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/06/29 11:59:41 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		redraw_pc_2(t_env *env, int pc, int len)
{
	int x;
	int y;
	int color;

	pc -= len;
	if (pc < 0)
		pc += MEM_SIZE;
	x = pc % 64 * 3;
	y = pc / 64;
	color = mvwinch(env->mem, y, x) & A_COLOR;
	if (color == COLOR_PAIR(12))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 1, NULL);
	else if (color == COLOR_PAIR(8))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 4, NULL);
	else if (color == COLOR_PAIR(9))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 5, NULL);
	else if (color == COLOR_PAIR(10))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 6, NULL);
	else if (color == COLOR_PAIR(11))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 7, NULL);
}

static void		redraw_pc(t_env *env, int pc, int len)
{
	int x;
	int y;
	int color;

	if (pc >= MEM_SIZE)
		pc -= MEM_SIZE;
	x = pc % 64 * 3;
	y = pc / 64;
	color = mvwinch(env->mem, y, x) & A_COLOR;
	if (color == COLOR_PAIR(1))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 12, NULL);
	else if (color == COLOR_PAIR(4))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 8, NULL);
	else if (color == COLOR_PAIR(5))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 9, NULL);
	else if (color == COLOR_PAIR(6))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 10, NULL);
	else if (color == COLOR_PAIR(7))
		mvwchgat(env->mem, y, x, 2, A_NORMAL, 11, NULL);
	redraw_pc_2(env, pc, len);
}

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
	else
		env->process[j].pc++;
	if (env->option == 1 || env->option == 2)
		redraw_pc(env, env->process[j].pc, env->process[j].pc - save);
}
