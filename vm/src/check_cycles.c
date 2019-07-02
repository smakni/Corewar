/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:38:30 by smakni            #+#    #+#             */
/*   Updated: 2019/07/02 19:24:01 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_cycles(t_env *env, unsigned j)
{
	int index;

	index = env->memory[env->process[j].pc];
	if (index > 16 || index < 1)
		return (0);
	env->process[j].op.code = index;
	env->process[j].op.encode = env->memory[env->process[j].pc + 1];
	return (env->op_cycles[index]);
}
