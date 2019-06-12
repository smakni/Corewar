/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:52:07 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/12 17:36:08 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

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

void		op_lfork(t_env *env, unsigned int j)
{
	int	index;

	env->champ[j].op.name = "lfork";
	if (env->nb_champs >= ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->champ[env->nb_champs] = env->champ[j];
	env->champ[env->nb_champs].cycle_to_life = env->cycle_index;
	index = read_bytes(env->memory, env->champ[j].pc + 1, IND_SIZE);
	if (index < 0)
		index += MEM_SIZE;
	env->champ[env->nb_champs].pc += index;
	if (env->champ[env->nb_champs].pc >= MEM_SIZE)
		env->champ[env->nb_champs].pc %= MEM_SIZE;
	env->champ[env->nb_champs].nb_live = env->champ[j].nb_live;
	env->champ[env->nb_champs].cycles = check_cycles(env, env->nb_champs);
	env->nb_champs++;
	env->champ[j].pc += 3;
}
