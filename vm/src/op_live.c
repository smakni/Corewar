/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/11 15:25:31 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	op_live_visu(t_env *env, unsigned j, unsigned id)
{
	int		color;
	int		x;
	int		y;

	x = env->champ[j].pc % 64 * 3;
	y = env->champ[j].pc / 64;

	if (id == (unsigned)-1)
	{
		color = 13;
//		env->champ[j].color2 = 4;
	}
	else if (id == (unsigned)-2)
		{
			color = 14;
		//env->champ[j].color2 = 5;
	}
	else if (id == (unsigned)-3)
		{
			color = 15;
		//env->champ[j].color2 = 6;
	}
	else if (id == (unsigned)-4)
	{
		color = 16;
		//env->champ[j].color2 = 7;
	}
	mvwchgat(env->mem, y, x, 2, A_NORMAL, color, NULL);
	env->champ[j].live = env->champ[j].pc;
}

void		op_live(t_env *env, unsigned j)
{
	unsigned int id;

	env->champ[j].op.name = "live";
	env->champ[j].live = -1;
	id = (unsigned)read_bytes(env->memory, env->champ[j].pc + 1, 4);
	save_param(env, j, id, IND_CODE, 0);
	if (id == (unsigned)-1)
		env->live[0].last_live = env->cycle_index;
	else if (id == (unsigned)-2)
		env->live[1].last_live = env->cycle_index;	
	else if (id == (unsigned)-3)
		env->live[2].last_live = env->cycle_index;	
	else if (id == (unsigned)-4)
		env->live[3].last_live = env->cycle_index;	
	if (env->visu == 1 && (id == (unsigned)-1 || id == (unsigned)-2 || id == (unsigned)-3 || id == (unsigned)-4))
		op_live_visu(env, j, id);
	env->champ[j].nb_live++;
	env->champ[j].pc += 5;
}