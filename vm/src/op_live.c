/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/06/05 15:08:02 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_env *env, unsigned j)
{
	unsigned int id;

	env->champ[j].op.name = "live";
	id = (unsigned)read_bytes(env->memory, env->champ[j].pc + 4, 4);
	if (env->champ[j].player_nb == id)
		env->champ[j].last_live = env->cycle_index;
	env->champ[j].nb_live++;
	env->champ[j].pc += 5;
}
