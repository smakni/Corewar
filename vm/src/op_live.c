/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:05:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/20 15:52:31 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_env *env, int j)
{
	unsigned int id;

	id = read_multi_bytes(env->memory, env->champ[j].pc + 4, 4);
	ft_printf("ID = %.2x\n", id);
	if (id == 0xffffffff)
		env->champ[0].lives++;
	else if (id == 0xfffffffe)
		env->champ[1].lives++;
	else if (id == 0xfffffffd)
		env->champ[2].lives++;
	else if (id == 0xfffffffc)
		env->champ[3].lives++;
}