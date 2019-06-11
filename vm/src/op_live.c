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

void		op_live(t_env *env, unsigned j)
{
	unsigned int id;

	env->champ[j].op.name = "live";
	id = (unsigned)read_bytes(env->memory, env->champ[j].pc + 1, 4);
	save_param(env, j, id, IND_CODE, 0);
	if (id >= (unsigned)-4 && id < 0)
		env->live[-id].last_live = env->cycle_index;
	env->champ[j].nb_live++;
	env->champ[j].pc += 5;
}
