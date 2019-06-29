/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/29 12:41:28 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	op_live_visu(t_env *env, unsigned j, unsigned id)
{
	int		color;
	int		x;
	int		y;

	x = env->process[j].pc % 64 * 3;
	y = env->process[j].pc / 64;
	color = 0;
	if (id == (unsigned)-1)
		color = 13;
	else if (id == (unsigned)-2)
		color = 14;
	else if (id == (unsigned)-3)
		color = 15;
	else if (id == (unsigned)-4)
		color = 16;
	protect_mvwchgat(env, y, x, color);
	env->process[j].live = env->process[j].pc;
}

void		op_live(t_env *env, unsigned j)
{
	unsigned int id;

	env->process[j].op.name = "live";
	env->process[j].live = -1;
	id = (unsigned)read_bytes(env->process[j].op.saved, 1, 4);
	if (env->verb == 1)
		save_ind_param(env, j, id, 0);
	if (id == (unsigned)-1)
		env->player[0].last_live = env->cycle_index;
	else if (id == (unsigned)-2)
		env->player[1].last_live = env->cycle_index;
	else if (id == (unsigned)-3)
		env->player[2].last_live = env->cycle_index;
	else if (id == (unsigned)-4)
		env->player[3].last_live = env->cycle_index;
	if ((env->option == 1 || env->option == 2)
			&& (id == (unsigned)-1 || id == (unsigned)-2
			|| id == (unsigned)-3 || id == (unsigned)-4))
		op_live_visu(env, j, id);
	env->live_period++;
	env->process[j].nb_live++;
	env->process[j].pc += 5;
	env->process[j].last_live = env->cycle_index;
}
