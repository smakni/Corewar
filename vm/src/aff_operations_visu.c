/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations_visu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/14 17:52:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void print_pc(t_env *env, unsigned j, int save)
{
	int i;

	i = 0;
	if (save == 0 && env->champ[j].pc == 0)
		wprintw(env->infos, "ADV %d (%#.4x -> %#.4x) ",
				env->champ[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		wprintw(env->infos, "ADV %d (%s -> %#.4x) ",
				env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else if (env->champ[j].pc == 0)
		wprintw(env->infos, "ADV %d (%s -> %#.4x) ",
				env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else
		wprintw(env->infos, "ADV %d (%#.4x -> %#.4x) ",
				env->champ[j].pc - save, save, env->champ[j].pc);
	while (save + i < env->champ[j].pc)
		wprintw(env->infos, "%.2x ", env->memory[(save + i++) % MEM_SIZE]);
	ft_putendl("");
	wattroff(env->infos, COLOR_PAIR(env->champ[j].color));
	wrefresh(env->infos);
}

void aff_operations_visu(t_env *env, unsigned j, int save)
{
	int i;
	int tmp;

	i = 0;
	if (env->champ[j].color == 4)
	{
		wmove(env->infos, 32, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 33, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 34, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 35, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 32, 0);
	}
	else if (env->champ[j].color == 5)
	{
		wmove(env->infos, 36, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 37, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 38, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 39, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 36, 0);
	}
	else if (env->champ[j].color == 6)
	{
		wmove(env->infos, 40, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 41, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 42, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 43, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 40, 0);
	}
	else if (env->champ[j].color == 7)
	{
		wmove(env->infos, 44, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 45, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 46, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 47, 0);
		wclrtoeol(env->infos);
		wmove(env->infos, 44, 0);
	}
	wattron(env->infos, COLOR_PAIR(env->champ[j].color));
	if (env->champ[j].op.name != NULL)
		wprintw(env->infos, "Process %4d | ", j + 1);
	if (env->champ[j].op.saved[0] == 0x09 && env->champ[j].carry == 1)
		wprintw(env->infos, "zjmp %d OK\n", read_bytes(env->champ[j].op.saved, 1, 2));
	else if (env->champ[j].op.saved[0] == 0x09 && env->champ[j].carry == 0)
	{
		wprintw(env->infos, "zjmp %d FAILED\n", read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] == 0x0c)
	{
		wprintw(env->infos, "fork %d (%d)\n", read_bytes(env->champ[j].op.saved, 1, 2),
				save + read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] == 0x0f)
	{
		wprintw(env->infos, "lfork %d (%d)\n", read_bytes(env->champ[j].op.saved, 1, 2),
				save + read_bytes(env->champ[j].op.saved, 1, 2));
		print_pc(env, j, save);
	}
	else if (env->champ[j].op.saved[0] != 0x0c)
	{
		if (env->champ[j].op.name != NULL)
			wprintw(env->infos, "%s", env->champ[j].op.name);
		while (env->champ[j].op.param[i])
			wprintw(env->infos, " %s", env->champ[j].op.param[i++]);
		if (env->champ[j].op.saved[0] == 0x01 && (ft_strcmp(env->champ[j].op.param[0], "-1") == 0 || ft_strcmp(env->champ[j].op.param[0], "-2") == 0 || ft_strcmp(env->champ[j].op.param[0], "-3") == 0 || ft_strcmp(env->champ[j].op.param[0], "-4") == 0))
			wprintw(env->infos, "\nPlayer %d (%s) is said to be alive",
					env->champ[j].nb + 1, env->live[env->champ[j].nb].header.prog_name);
		else if (env->champ[j].op.saved[0] == 0x0b && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[1]) + ft_atoi(env->champ[j].op.param[2]);
			wprintw(env->infos, "\n -> store to %s + %s = %d (with pc and mod %d)",
					env->champ[j].op.param[1], env->champ[j].op.param[2],
					tmp, save + (tmp % IDX_MOD));
		}
		else if (env->champ[j].op.saved[0] == 0x0a && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[0]) + ft_atoi(env->champ[j].op.param[1]);
			wprintw(env->infos, "\n -> load from %s + %s = %d (with pc and mod %d)",
					env->champ[j].op.param[0], env->champ[j].op.param[1],
					tmp, save + (tmp % IDX_MOD));
		}
		if (env->champ[j].op.name != NULL)
			wprintw(env->infos, "\n");
		print_pc(env, j, save);
		while (env->champ[j].op.param[i])
			free(env->champ[j].op.param[i++]);
	}
}