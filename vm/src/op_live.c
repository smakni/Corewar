/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/07 14:30:12 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_env *env, unsigned j)
{
	unsigned int id;

	env->champ[j].op.name = "live";
	id = (unsigned)read_bytes(env->memory, env->champ[j].pc + 1, 4);
	save_param(env, j, id, IND_CODE, 0);
	if (env->champ[j].id == id)
		env->live[env->champ[j].nb].last_live = env->cycle_index;
	env->champ[j].nb_live++;
	env->champ[j].pc += 5;
}
