/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/07 19:15:49 by sabri            ###   ########.fr       */
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
		ft_printf("%s", env->champ[j].op.name);
		while (env->champ[j].op.param[i])
			ft_printf(" %s", env->champ[j].op.param[i++]);
		if (env->memory[save] == 01
				&& (ft_strcmp(env->champ[j].op.param[0], "-1") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-2") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-3") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-4") == 0))
			ft_printf("\nPlayer %d (%s) is said to be alive",
						UINT_MAX - ft_atoi(env->champ[j].op.param[0]),
						env->live[UINT_MAX - ft_atoi(env->champ[j].op.param[0])].header.prog_name);
		ft_printf("\nADV %d (%#.4x -> %#.4x) ",
						env->champ[j].pc - save, save, env->champ[j].pc);
		i = 0;
		while (save + i < env->champ[j].pc)
		{
			ft_printf("%.2x ", env->memory[save + i]);
			i++;
		}
		ft_putendl("");
	}
}

void	save_param(t_env *env, int j, int value, int code, int index)
{
	char *tmp;

	tmp = ft_itoa(value);
	if (code == REG_CODE)
	{
		env->champ[j].op.param[index] = "r";
		env->champ[j].op.param[index] = ft_strjoin(env->champ[j].op.param[index], tmp);
	}
	else if (code == IND_CODE)
		env->champ[j].op.param[index] = ft_strjoin(env->champ[j].op.param[index], tmp);
	else if (code == DIR_CODE)
	{
		env->champ[j].op.param[index] = "%";
		env->champ[j].op.param[index] = ft_strjoin(env->champ[j].op.param[index], tmp);
	}
	env->champ[j].op.param[3] = NULL;
}