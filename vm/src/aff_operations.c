/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/06 19:16:39 by smakni           ###   ########.fr       */
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
	else if (env->memory[save] == 0x0c)
		ft_printf("fork %d (%d)\n", read_bytes(env->memory, save + 1, 2),
								save + read_bytes(env->memory, save + 1, 2));
	else if (env->memory[save] == 0x0f)
		ft_printf("lfork %d (%d)\n", read_bytes(env->memory, save + 1, 2),
								save + read_bytes(env->memory, save + 1, 2));
	else
	{
		ft_printf("%s%s\n", env->champ[j].op.name, env->champ[j].op.param);
		if (env->memory[save] == 01
				&& ft_strcmp(env->champ[j].op.param, " -1") == 0)
			ft_printf("Player %d (%s) is said to be alive\n",
							env->champ[j].nb + 1,
								env->champ[j].header.prog_name);
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
						env->champ[j].pc - save, save, env->champ[j].pc);
		while (save + i < env->champ[j].pc)
		{
			ft_printf("%.2x ", env->memory[save + i]);
			i++;
		}
		ft_putendl("");
	}
}

void	save_param(t_env *env, int j, int value, int code)
{
	if (code == REG_CODE)
	{
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, " r");
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, ft_itoa(value));
	}
	else if (code == IND_CODE)
	{
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, " ");
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, ft_itoa(value));
	}
	else if (code == DIR_CODE)
	{
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, " %");
		env->champ[j].op.param = ft_strjoin(env->champ[j].op.param, ft_itoa(value));
	}
	
}