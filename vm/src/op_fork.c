/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 00:00:08 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/10 14:43:23 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

static int	ft_realloc_tab(t_env *env)
{
	t_champ *tmp;
	unsigned 	i;

	env->nb_realloc++;
	i = 0;
	if (!(tmp = (t_champ *)malloc(sizeof(t_champ)
							* (ARR_SIZE * env->nb_realloc))))
	{
		ft_memdel((void *)&env->champ);
		return (-1);
	}
	while (i < env->nb_champs)
	{
		tmp[i] = env->champ[i];
		i++;
	}
	ft_memdel((void *)&env->champ);
	env->champ = tmp;
	return (0);
}

void		op_fork(t_env *env, unsigned j)
{
	int	index;

	env->champ[j].op.name = "fork";
	if (env->nb_champs >= ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->champ[env->nb_champs] = env->champ[j];
	index = read_bytes(env->memory, env->champ[j].pc + 1, 2);
	env->champ[env->nb_champs].pc += index % IDX_MOD;
	env->champ[env->nb_champs].nb_live = 0;
	env->champ[env->nb_champs].cycles = check_cycles(env, env->nb_champs);
	//ft_printf("PC = %d\n", env->champ[env->nb_champs].pc);
	env->nb_champs++;
	//env->champ[j].cycles = check_cycles(env, j);
	env->champ[j].pc += 3;
}
