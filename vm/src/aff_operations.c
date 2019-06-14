/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/14 14:43:01 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static	void	print_pc(t_env *env, unsigned j, int save)
{
	int			i;

	i = 0;
	if (save == 0 && env->champ[j].pc == 0)
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else if (env->champ[j].pc == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->champ[j].pc - save, save, env->champ[j].pc);
	while (save + i < env->champ[j].pc)
		ft_printf("%.2x ", env->memory[(save + i++) % MEM_SIZE]);
	ft_putendl("");
}

void 			aff_operations(t_env *env, unsigned j, int save)
{
	int 		i;
	unsigned	nb_params;
	int			tmp;

	i = 0;
	nb_params = 0;
	if (env->champ[j].op.name != NULL)
		ft_printf("P %4d | ", j + 1);
	if (env->champ[j].op.saved[0] == 0x09 && env->champ[j].carry == 1)
		ft_printf("zjmp %d OK\n", read_bytes(env->champ[j].op.saved, 1, 2));
	else if (env->champ[j].op.saved[0] == 0x09 && env->champ[j].carry == 0)
	{
		ft_printf("zjmp %d FAILED\n", read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] == 0x0c)
	{
		ft_printf("fork %d (%d)\n", read_bytes(env->champ[j].op.saved, 1, 2),
								save + read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] == 0x0f)
	{
		ft_printf("lfork %d (%d)\n", read_bytes(env->champ[j].op.saved, 1, 2),
								save + read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] != 0x0c)
	{
		if (env->champ[j].op.name != NULL)
			ft_printf("%s", env->champ[j].op.name);
		while (env->champ[j].op.param[i])
			ft_printf(" %s", env->champ[j].op.param[i++]);
		if (env->champ[j].op.saved[0] == 0x01
				&& (ft_strcmp(env->champ[j].op.param[0], "-1") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-2") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-3") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-4") == 0))
			ft_printf("\nPlayer %d (%s) is said to be alive",
						env->champ[j].nb + 1, env->live[env->champ[j].nb].header.prog_name);
		else if (env->champ[j].op.saved[0] == 0x0b && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[1]) + ft_atoi(env->champ[j].op.param[2]);
			ft_printf("\n       | -> store to %s + %s = %d (with pc and mod %d)",
						env->champ[j].op.param[1], env->champ[j].op.param[2],
						tmp, save + (tmp % IDX_MOD));
		}
		else if (env->champ[j].op.saved[0] == 0x0a && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[0]) + ft_atoi(env->champ[j].op.param[1]);
			ft_printf("\n       | -> load from %s + %s = %d (with pc and mod %d)",
						env->champ[j].op.param[0], env->champ[j].op.param[1],
						tmp, save + (tmp % IDX_MOD));
		}
		if (env->champ[j].op.name != NULL)
			ft_putendl("");
		print_pc(env, j, save);
		while (env->champ[j].op.param[i])
			free(env->champ[j].op.param[i++]);
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