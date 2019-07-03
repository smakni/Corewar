/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:38:30 by smakni            #+#    #+#             */
/*   Updated: 2019/07/03 14:55:23 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_cycles(t_env *env, unsigned j)
{
	int index;

	index = env->memory[env->process[j].pc];
	if (index > 16 || index < 1)
		return (0);
	//ft_bzero(&(env->process[j].op.param), (sizeof(char*) * 3));
	env->process[j].op.code = index;
	return (env->op_cycles[index]);
}
