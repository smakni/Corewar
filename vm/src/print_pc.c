/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:02:54 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/08 15:11:34 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		reset_verbos(t_env *env, unsigned j)
{
	int i;

	i = 0;
	while (i < 4)
		ft_strdel(&(env->process[j].op.param[i++]));
	env->process[j].op.name = NULL;
}

void			print_pc(t_env *env, unsigned j, int save)
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
	reset_verbos(env, j);
}
