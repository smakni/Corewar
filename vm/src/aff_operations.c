/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by sabri             #+#    #+#             */
/*   Updated: 2019/06/04 14:45:35 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void 	aff_operations(t_env *env, unsigned j, int save)
{
	int i;

	i = 0;
	if (env->memory[save] == 0x09 && env->champ[j].carry == 1)
		ft_printf("PROC[%d]>>PC[%d]>>ZJMP>>>>[%d]\n", j, save
						,read_bytes(env->memory, save + 1, 2));
	else if (env->memory[save] == 0x0c)
		ft_printf("PROC[%d]>>PC[%d]>>FORK>>>>[%d]\n", j, save
						,read_bytes(env->memory, save + 1, 2));
	else
	{
		ft_printf("PROC[%d]>>PC[%d]>>OP>>>>[ ", j, save);
		while (save + i < env->champ[j].pc)
		{
			ft_printf("%.2x ", env->memory[save + i]);
			i++;
		}
		ft_printf("]\n");
	}
}