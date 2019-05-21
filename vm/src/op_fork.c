/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 22:51:17 by sabri             #+#    #+#             */
/*   Updated: 2019/05/21 16:59:41 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

static int	ft_realloc_tab(t_env *env)
{
	t_champ *tmp;
	int 	i;

	env->nb_realloc++;
	i = 0;
	if (!(tmp = (t_champ *)malloc(sizeof(t_champ)
							* (ARR_SIZE * env->nb_realloc))))
		return (-1);
	while (i < env->nb_champs)
	{
		tmp[i] = env->champ[i];
		i++;
	}
	ft_memdel((void *)&env->champ);
	env->champ = tmp;
	return (0);
}

int			op_fork(t_env *env, int j)
{
	if (env->nb_champs == ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
			return (-1);
	env->champ[env->nb_champs] = env->champ[j];
	env->champ[env->nb_champs].pc = read_multi_bytes(env->memory,
								env->champ[env->nb_champs].pc + 2, 2);
	env->champ[env->nb_champs].lives = 0;
	env->nb_champs++;
	env->champ[j].cycles = check_cycles(env, j);
	return (0);
}