/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/24 16:07:49 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_env *env, int j)
{
	unsigned int id;
	
	if (env->champ[j].pc + 4 > MEM_SIZE)
	{
		env->champ[j].pc -= MEM_SIZE;
		env->champ[j].pc += 4;
	}
	id = (unsigned)read_multi_bytes(env->memory, env->champ[j].pc + 4, 4);
	//ft_printf("ID = %x\n", id);
	if (env->champ[j].player_nb == id)
		env->champ[j].last_live = env->cycle_index;
	env->champ[j].nb_live++;
	env->champ[j].pc += 5;
}
