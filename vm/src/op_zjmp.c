/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:20:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/24 21:17:23 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	op_zjmp(t_env *env, unsigned j)
{
	int index;
	int	save;

	save = env->champ[j].pc;
	if (env->champ[j].carry == 1)
	{
		if (env->memory[env->champ[j].pc + 1] >= 254)
		{
			index =  env->memory[env->champ[j].pc + 1] - env->memory[env->champ[j].pc + 2] + 1;
			env->champ[j].pc -= (index % IDX_MOD);
		}
		else
		{
			index = read_multi_bytes(env->memory, env->champ[j].pc + 2, 2);
			env->champ[j].pc += (index % IDX_MOD);
		}
	//	ft_printf("INDEX_JUMP = %d\n", index);
	//	ft_printf("pc = %d\n", env->champ[j].pc);
				//exit (0);
		env->champ[j].pc %= MEM_SIZE;
	}
	else
		env->champ[j].pc += 3;
	if (env->visu == 1)
		redraw_pc(env, env->champ[j].pc, env->champ[j].player_nb, env->champ[j].pc - save);
}