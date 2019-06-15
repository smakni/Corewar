/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 00:00:08 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/13 18:00:01 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

static int	ft_realloc_tab(t_env *env)
{
	t_proc *tmp;
	unsigned 	i;

	env->nb_realloc++;
	i = 0;
	if (!(tmp = malloc(sizeof(t_player) * (ARR_SIZE * env->nb_realloc))))
	{
		ft_memdel((void *)&env->proc);
		return (-1);
	}
	while (i < env->nb_proc)
	{
		tmp[i] = env->proc[i];
		i++;
	}
	ft_memdel((void *)&env->proc);
	env->proc = tmp;
	return (0);
}

void		op_fork(t_env *env, unsigned int j)
{
	int	index;

	env->proc[j].op.name = "fork";
	if (env->nb_proc >= ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->proc[env->nb_proc] = env->proc[j];
	env->proc[env->nb_proc].cycle_to_life = env->cycle_index;
	index = read_bytes(env->proc[j].op.saved, 1, IND_SIZE) % IDX_MOD;
	ft_bzero(&(env->proc[env->nb_proc].op), sizeof(t_op));
	env->proc[env->nb_proc].pc += index;
	if (env->proc[env->nb_proc].pc < 0)
		env->proc[env->nb_proc].pc += MEM_SIZE;
	else if (env->proc[j].pc >= MEM_SIZE)
		env->proc[j].pc %= MEM_SIZE;
	env->proc[env->nb_proc].nb_live = env->proc[j].nb_live;
	env->proc[env->nb_proc].cycles = check_cycles(env, env->nb_proc);
	env->proc[env->nb_proc].bold = 0;
	env->proc[env->nb_proc].live = -1;
	//ft_printf("PC = %d\n", env->proc[env->nb_proc].pc);
	env->nb_proc++;
	env->proc[j].pc += 3;
}
