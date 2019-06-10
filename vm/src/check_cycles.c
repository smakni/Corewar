/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:38:30 by smakni            #+#    #+#             */
/*   Updated: 2019/06/10 22:01:20 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_cycles(t_env *env, unsigned j)
{
	int op_cycles[17];
	int index;

	op_cycles[0] = 1;
	op_cycles[1] = 10;
	op_cycles[2] = 5;
	op_cycles[3] = 5;
	op_cycles[4] = 10;
	op_cycles[5] = 10;
	op_cycles[6] = 6;
	op_cycles[7] = 6;
	op_cycles[8] = 6;
	op_cycles[9] = 20;
	op_cycles[10] = 25;
	op_cycles[11] = 25;
	op_cycles[12] = 800;
	op_cycles[13] = 10;
	op_cycles[14] = 50;
	op_cycles[15] = 1000;
	op_cycles[16] = 2;
	index = env->memory[env->champ[j].pc];
	if (index > 16 || index < 0)
		return (0);
	return (op_cycles[index]);
}
