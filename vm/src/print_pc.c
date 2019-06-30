/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:02:54 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/30 13:03:34 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_pc(t_env *env, unsigned j, int save)
{
	int	i;

	i = 0;
	if (save == 0 && env->process[j].pc == 0)
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->process[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->process[j].pc - save, "0x0000", env->process[j].pc);
	else if (env->process[j].pc == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->process[j].pc - save, "0x0000", env->process[j].pc);
	else
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->process[j].pc - save, save, env->process[j].pc);
	while (save + i < env->process[j].pc)
		ft_printf("%.2x ", env->memory[(save + i++) % MEM_SIZE]);
	ft_putendl("");
}
