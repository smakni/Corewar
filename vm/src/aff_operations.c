/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by sabri             #+#    #+#             */
/*   Updated: 2019/06/05 17:39:18 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void 	aff_operations(t_env *env, unsigned j, int save)
{
	int 		i;
	unsigned	nb_params;

	i = 0;
	nb_params = 0;
	ft_printf("P %4d | ", j + 1);
	if (env->memory[save] == 0x09 && env->champ[j].carry == 1)
		ft_printf("zjmp %d OK >> %d\n", read_bytes(env->memory, save + 1, 2),
								env->champ[j].pc + read_bytes(env->memory, save + 1, 2));
	else if (env->memory[save] != 0x09)
	{
		if (env->memory[save] == 0x0c)
			ft_printf("fork %d (%d)\n", read_bytes(env->memory, save + 1, 2),
										save + read_bytes(env->memory, save + 1, 2));
		else if (env->memory[save] == 0x0f)
			ft_printf("lfork %d (%d)\n", read_bytes(env->memory, save + 1, 2),
										save + read_bytes(env->memory, save + 1, 2));
		else
		{
			ft_printf("%s\n", env->champ[j].op.name);
			//while (nb_params < env->champ[j].op.nb_params) 
			//	ft_printf("%d,", env->champ[j].op.param[nb_params++]);
		}
		ft_printf("ADV %d (%#.4x -> %#.4x) ", env->champ[j].pc - save, save, env->champ[j].pc);
		while (save + i < env->champ[j].pc)
		{
			ft_printf("%.2x ", env->memory[save + i]);
			i++;
		}
		ft_putendl("");
	}
}