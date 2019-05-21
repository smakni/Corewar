/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/21 15:51:17 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_env *env, int j)
{
	unsigned int id;
	

	id = read_multi_bytes(env->memory, env->champ[j].pc + 4, 4);
	ft_printf("ID = %.2x\n", id);
	if (env->champ[j].player_nb == id)
		env->champ[j].lives++;
	if (id == 0xffffffff)
		env->champ_live[0] += 1;
	else if (id == 0xfffffffe)
		env->champ_live[1] += 1;
	else if (id == 0xfffffffd)
		env->champ_live[2] += 1;
	else if (id == 0xfffffffc)
		env->champ_live[3] += 1;
}
