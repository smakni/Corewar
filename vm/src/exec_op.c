/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/06/27 15:44:09 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void			protect_mvwchgat(t_env *env, int y, int x, int color)
{
	if (mvwchgat(env->mem, y, x, 2, A_NORMAL, color, NULL) == ERR)	
		exit_clean(env);
}

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
		protect_mvwchgat(env, y, x, 1);
	else if (color == COLOR_PAIR(8))
		protect_mvwchgat(env, y, x, 4);
	else if (color == COLOR_PAIR(9))
		protect_mvwchgat(env, y, x, 5);
	else if (color == COLOR_PAIR(10))
		protect_mvwchgat(env, y, x, 6);
	else if (color == COLOR_PAIR(11))
		protect_mvwchgat(env, y, x, 7);
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
		protect_mvwchgat(env, y, x, 12);
	else if (color == COLOR_PAIR(4))
		protect_mvwchgat(env, y, x, 8);
	else if (color == COLOR_PAIR(5))
		protect_mvwchgat(env, y, x, 9);
	else if (color == COLOR_PAIR(6))
		protect_mvwchgat(env, y, x, 10);
	else if (color == COLOR_PAIR(7))
		protect_mvwchgat(env, y, x, 11);
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
		protect_mvwchgat(env, y, x, 4);
	else if (color == COLOR_PAIR(14))
		protect_mvwchgat(env, y, x, 5);
	else if (color == COLOR_PAIR(15))
		protect_mvwchgat(env, y, x, 6);
	else if (color == COLOR_PAIR(16))
		protect_mvwchgat(env, y, x, 7);
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
		else if (env->verb == 1)
			verbos(env, j, save);
	}
	else
		env->process[j].pc++;
	if (env->option == 1 || env->option == 2)
		redraw_pc(env, env->process[j].pc, env->process[j].pc - save);
}
