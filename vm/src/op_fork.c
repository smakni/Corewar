/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 22:51:17 by sabri             #+#    #+#             */
/*   Updated: 2019/05/29 15:12:25 by smakni           ###   ########.fr       */
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

	//aff_memory(env, j, 3);
	if (env->nb_champs >= ARR_SIZE * env->nb_realloc)
		if (ft_realloc_tab(env) == -1)
		{
			env->err_code = 2;
			env->err_msg = "Fail to malloc.";
			return ;
		}
	env->champ[env->nb_champs] = env->champ[j];
	if (env->memory[env->champ[j].pc + 2] == 0)
		env->champ[env->nb_champs].pc = 0;
	if (env->memory[env->champ[j].pc + 1] >= 254)
	{
		index =  env->memory[env->champ[j].pc + 1] - env->memory[env->champ[j].pc + 2] + 1;
		env->champ[env->nb_champs].pc -= (index % IDX_MOD);
	}
	else
	{
		index = read_multi_bytes(env->memory, env->champ[j].pc + 2, 2) + 1;
		env->champ[env->nb_champs].pc += (index % IDX_MOD);
	}
	env->champ[env->nb_champs].nb_live = 0;
	//ft_printf("PC = %d\n", env->champ[env->nb_champs].pc);
	env->nb_champs++;
	env->champ[j].cycles = check_cycles(env, j);
	env->champ[j].pc += 3;
}
