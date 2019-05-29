/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:34 by sabri             #+#    #+#             */
/*   Updated: 2019/05/29 14:52:38 by smakni           ###   ########.fr       */
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

void		op_lfork(t_env *env, unsigned j)
{
	int index;
	
	if (env->nb_champs == ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->champ[env->nb_champs] = env->champ[j];
	if (env->memory[env->champ[j].pc + 1] >= 254)
	{
		index =  env->memory[env->champ[j].pc + 1] - env->memory[env->champ[j].pc + 2] + 1;
		env->champ[env->nb_champs].pc -= (index % MEM_SIZE);
	}
	else
	{
		index = read_multi_bytes(env->memory, env->champ[j].pc + 2, 2) + 1;
		env->champ[env->nb_champs].pc += (index % MEM_SIZE);
	}
	env->champ[env->nb_champs].nb_live = 0;
	env->nb_champs++;
	env->champ[j].cycles = check_cycles(env, j);
	env->champ[j].pc += 3;
}
