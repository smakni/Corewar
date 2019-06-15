/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/14 17:52:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static	void	print_pc(t_env *env, unsigned j, int save)
{
	int			i;

	i = 0;
	if (save == 0 && env->proc[j].pc == 0)
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->proc[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->proc[j].pc - save, "0x0000", env->proc[j].pc);
	else if (env->proc[j].pc == 0)
		ft_printf("ADV %d (%s -> %#.4x) ",
			env->proc[j].pc - save, "0x0000", env->proc[j].pc);
	else
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
			env->proc[j].pc - save, save, env->proc[j].pc);
	while (save + i < env->proc[j].pc)
		ft_printf("%.2x ", env->memory[(save + i++) % MEM_SIZE]);
	ft_putendl("");
}

void 			aff_operations(t_env *env, unsigned j, int save)
{
	int 		i;
	int			tmp;

	i = 0;
	if (env->proc[j].op.name != NULL)
		ft_printf("P %4d | ", j + 1);
	if (env->proc[j].op.saved[0] == 0x09 && env->proc[j].carry == 1)
		ft_printf("zjmp %d OK\n", read_bytes(env->proc[j].op.saved, 1, 2));
	else if (env->proc[j].op.saved[0] == 0x09 && env->proc[j].carry == 0)
	{
		ft_printf("zjmp %d FAILED\n", read_bytes(env->proc[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->proc[j].op.saved[0] == 0x0c)
	{
		ft_printf("fork %d (%d)\n", read_bytes(env->proc[j].op.saved, 1, 2),
								save + read_bytes(env->proc[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->proc[j].op.saved[0] == 0x0f)
	{
		ft_printf("lfork %d (%d)\n", read_bytes(env->proc[j].op.saved, 1, 2),
								save + read_bytes(env->proc[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->proc[j].op.saved[0] != 0x0c)
	{
		if (env->proc[j].op.name != NULL)
			ft_printf("%s", env->proc[j].op.name);
		while (env->proc[j].op.param[i])
			ft_printf(" %s", env->proc[j].op.param[i++]);
		if (env->proc[j].op.saved[0] == 0x01
				&& (ft_strcmp(env->proc[j].op.param[0], "-1") == 0
					|| ft_strcmp(env->proc[j].op.param[0], "-2") == 0
					|| ft_strcmp(env->proc[j].op.param[0], "-3") == 0
					|| ft_strcmp(env->proc[j].op.param[0], "-4") == 0))
			ft_printf("\nPlayer %d (%s) is said to be alive",
						env->proc[j].nb + 1, env->player[env->proc[j].nb].header.prog_name);
		else if (env->proc[j].op.saved[0] == 0x0b && env->proc[j].check_args == 1)
		{
			tmp = ft_atoi(env->proc[j].op.param[1]) + ft_atoi(env->proc[j].op.param[2]);
			ft_printf("\n       | -> store to %s + %s = %d (with pc and mod %d)",
						env->proc[j].op.param[1], env->proc[j].op.param[2],
						tmp, save + (tmp % IDX_MOD));
		}
		else if (env->proc[j].op.saved[0] == 0x0a && env->proc[j].check_args == 1)
		{
			tmp = ft_atoi(env->proc[j].op.param[0]) + ft_atoi(env->proc[j].op.param[1]);
			ft_printf("\n       | -> load from %s + %s = %d (with pc and mod %d)",
						env->proc[j].op.param[0], env->proc[j].op.param[1],
						tmp, save + (tmp % IDX_MOD));
		}
		if (env->proc[j].op.name != NULL)
			ft_putendl("");
		print_pc(env, j, save);
		while (env->proc[j].op.param[i])
			free(env->proc[j].op.param[i++]);
	}
}

void	save_param(t_env *env, int j, int value, int code, int index)
{
	char *tmp;

	tmp = ft_itoa(value);
	if (code == REG_CODE)
	{
		env->proc[j].op.param[index] = "r";
		env->proc[j].op.param[index] = ft_strjoin(env->proc[j].op.param[index], tmp);
	}
	else if (code == IND_CODE)
		env->proc[j].op.param[index] = ft_strjoin(env->proc[j].op.param[index], tmp);
	else if (code == DIR_CODE)
	{
		env->proc[j].op.param[index] = "%";
		env->proc[j].op.param[index] = ft_strjoin(env->proc[j].op.param[index], tmp);
	}
	env->proc[j].op.param[3] = NULL;
}
