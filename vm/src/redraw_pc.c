/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_pc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:54:38 by smakni            #+#    #+#             */
/*   Updated: 2019/07/02 19:54:41 by smakni           ###   ########.fr       */
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

void		redraw_pc(t_env *env, int pc, int len)
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