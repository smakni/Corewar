/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbos_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:18:58 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/30 13:05:38 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_pc_visu(t_env *env, unsigned j, int save)
{
	int i;

	i = 0;
	if (save == 0 && env->process[j].pc == 0)
		wprintw(env->verbos, "ADV %d (%#.4x -> %#.4x) ",
				env->process[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		wprintw(env->verbos, "ADV %d (%s -> %#.4x) ",
				env->process[j].pc - save, "0x0000", env->process[j].pc);
	else if (env->process[j].pc == 0)
		wprintw(env->verbos, "ADV %d (%s -> %#.4x) ",
				env->process[j].pc - save, "0x0000", env->process[j].pc);
	else
		wprintw(env->verbos, "ADV %d (%#.4x -> %#.4x) ",
				env->process[j].pc - save, save, env->process[j].pc);
	while (save + i < env->process[j].pc)
		wprintw(env->verbos, "%.2x ", env->memory[(save + i++) % MEM_SIZE]);
	wprintw(env->verbos, "\n");
	wattroff(env->verbos, COLOR_PAIR(env->process[j].color));
	protect_wrefresh(env, env->verbos);
}

static void	verbos_forklfork_visu(t_env *env, unsigned j, int save, char *str)
{
	wprintw(env->verbos, str, read_bytes(env->process[j].op.saved, 1, 2),
			save + read_bytes(env->process[j].op.saved, 1, 2));
	print_pc_visu(env, j, save);
}

static void	ldisti(t_env *env, unsigned j, int save, int op)
{
	int		tmp;

	if (op == 0)
	{
		tmp = ft_atoi(env->process[j].op.param[1])
			+ ft_atoi(env->process[j].op.param[2]);
		wprintw(env->verbos,
				"\n -> store to %s + %s = %d (with pc and mod %d)",
				env->process[j].op.param[1], env->process[j].op.param[2],
				tmp, save + (tmp % IDX_MOD));
	}
	else
	{
		tmp = ft_atoi(env->process[j].op.param[0])
			+ ft_atoi(env->process[j].op.param[1]);
		wprintw(env->verbos,
				"\n -> load from %s + %s = %d (with pc and mod %d)",
				env->process[j].op.param[0], env->process[j].op.param[1],
				tmp, save + (tmp % IDX_MOD));
	}
}

static void	verbos_visu_2(t_env *env, unsigned j, int save, int i)
{
	if (env->process[j].op.name != NULL)
		wprintw(env->verbos, "%s", env->process[j].op.name);
	while (env->process[j].op.param[i])
		wprintw(env->verbos, " %s", env->process[j].op.param[i++]);
	if (env->process[j].op.saved[0] == 0x01
			&& (ft_strcmp(env->process[j].op.param[0], "-1") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-2") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-3") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-4") == 0))
		wprintw(env->verbos, "\nPlayer %c (%s) is said to be alive",
				env->process[j].op.param[0][1],
				env->player[env->process[j].nb].header.prog_name);
	else if (env->process[j].op.saved[0] == 0x0b
			&& env->process[j].check_args == 1)
		ldisti(env, j, save, 0);
	else if (env->process[j].op.saved[0] == 0x0a
			&& env->process[j].check_args == 1)
		ldisti(env, j, save, 1);
	if (env->process[j].op.name != NULL)
		wprintw(env->verbos, "\n");
	print_pc_visu(env, j, save);
	while (env->process[j].op.param[i])
		free(env->process[j].op.param[i++]);
}

void		verbos_visu(t_env *env, unsigned j, int save)
{
	int i;

	i = 0;
	wattron(env->verbos, COLOR_PAIR(0));
	if (env->process[j].op.name != NULL)
		wprintw(env->verbos, "Process %4d | ", j + 1);
	if (env->process[j].op.saved[0] == 0x09 && env->process[j].carry == 1)
		wprintw(env->verbos, "zjmp %d OK\n",
				read_bytes(env->process[j].op.saved, 1, 2));
	else if (env->process[j].op.saved[0] == 0x09 && env->process[j].carry == 0)
	{
		wprintw(env->verbos, "zjmp %d FAILED\n",
				read_bytes(env->process[j].op.saved, 1, 2));
		print_pc_visu(env, j, save);
	}
	else if (env->process[j].op.code == 0x0c)
		verbos_forklfork_visu(env, j, save, "fork %d (%d)\n");
	else if (env->process[j].op.code == 0x0f)
		verbos_forklfork_visu(env, j, save, "lfork %d (%d)\n");
	else if (env->process[j].op.saved[0] != 0x0c)
		verbos_visu_2(env, j, save, i);
}
