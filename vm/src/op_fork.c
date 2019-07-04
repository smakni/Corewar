/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 00:00:08 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/04 13:02:28 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	set_fork_values(t_env *env, unsigned int j)
{
	env->process[env->nb_process].nb_live = env->process[j].nb_live;
	env->process[env->nb_process].cycles = 0;
	env->process[env->nb_process].bold = 0;
	env->process[env->nb_process].live = -1;
}

void		op_fork(t_env *env, unsigned int j)
{
	int	index;

	env->process[j].op.name = "fork";
	if (env->nb_process >= env->capacity)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->process[env->nb_process] = env->process[j];
	env->process[env->nb_process].cycle_to_life = env->cycle_index;
	index = read_bytes(env->process[j].op.saved, 1, IND_SIZE) % IDX_MOD;
	ft_bzero(&(env->process[env->nb_process].op), sizeof(t_op));
	env->process[env->nb_process].pc += index;
	if (env->process[env->nb_process].pc < 0)
		env->process[env->nb_process].pc += MEM_SIZE;
	else if (env->process[j].pc >= MEM_SIZE)
		env->process[j].pc %= MEM_SIZE;
	set_fork_values(env, j);
	env->nb_process++;
	env->living_proc++;
	env->process[j].pc += 3;
}
