/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:52:07 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/18 22:05:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	ft_realloc_tab(t_env *env)
{
	t_process *tmp;
	unsigned 	i;

	env->nb_realloc++;
	i = 0;
	if (!(tmp = malloc(sizeof(t_player)	* (ARR_SIZE * env->nb_realloc))))
	{
		ft_memdel((void *)&env->process);
		return (-1);
	}
	while (i < env->nb_process)
	{
		tmp[i] = env->process[i];
		i++;
	}
	ft_memdel((void *)&env->process);
	env->process = tmp;
	return (0);
}

void		op_lfork(t_env *env, unsigned int j)
{
	int	index;

	env->process[j].op.name = "lfork";
	if (env->nb_process >= ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->process[env->nb_process] = env->process[j];
	env->process[env->nb_process].cycle_to_life = env->cycle_index;
	index = read_bytes(env->process[j].op.saved, 1, IND_SIZE);
	ft_bzero(&(env->process[env->nb_process].op), sizeof(t_op));
	env->process[env->nb_process].pc += index;
	if (env->process[env->nb_process].pc < 0)
		env->process[env->nb_process].pc += MEM_SIZE;
	else if (env->process[j].pc >= MEM_SIZE)
		env->process[j].pc %= MEM_SIZE;
	env->process[env->nb_process].nb_live = env->process[j].nb_live;
	env->process[env->nb_process].cycles = 0;
	env->process[env->nb_process].bold = 0;
	env->process[env->nb_process].live = -1;
	env->nb_process++;
	env->process[j].pc += 3;
}
