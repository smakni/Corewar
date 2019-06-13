/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_operations_visu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:54 by smakni            #+#    #+#             */
/*   Updated: 2019/06/13 19:52:23 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
/*
static	void	print_pc(t_env *env, unsigned j, int save)
{
	int			i;

	i = 0;
	if (save == 0 && env->champ[j].pc == 0)
		mvwprintw(env->infos, 50, 6,"ADV %d (%#.4x -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", "0x0000");
	else if (save == 0)
		mvwprintw(env->infos, 50, 6,"ADV %d (%s -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else if (env->champ[j].pc == 0)
		mvwprintw(env->infos, 50, 6,"ADV %d (%s -> %#.4x) ",
			env->champ[j].pc - save, "0x0000", env->champ[j].pc);
	else
		mvwprintw(env->infos, 50, 6,"ADV %d (%#.4x -> %#.4x) ",
			env->champ[j].pc - save, save, env->champ[j].pc);
	while (save + i < env->champ[j].pc)
		mvwprintw(env->infos, 50, 6,"%.2x ", env->memory[save + i++]);
	ft_putendl("");
}
*/
void 			aff_operations_visu(t_env *env, unsigned j, int save)
{
	int 		i;
	unsigned	nb_params;
	int			tmp;
	int			line;

	i = 0;
	nb_params = 0;
	line = 0;
	return ;
	wmove(env->infos, 50, 1);
	wclrtoeol(env->infos);
	wmove(env->infos, 51, 1);
	wclrtoeol(env->infos);
	if (env->champ[j].op.name != NULL)
	{
		mvwprintw(env->infos, 50 + line, 6,"P %4d | ", j + 1);
		line++;
	}
	if (env->memory[save] == 0x09 && env->champ[j].carry == 1)
	{
		mvwprintw(env->infos, 50 + line, 6,"zjmp %d OK", read_bytes(env->memory, save + 1, 2));
		line++;
	}
	else if (env->memory[save] == 0x09 && env->champ[j].carry == 0)
	{
		mvwprintw(env->infos, 50 + line, 6,"zjmp %d FAILED", read_bytes(env->memory, save + 1, 2));
		line++;
	}
	else if (env->memory[save] == 0x0c)
	{
		mvwprintw(env->infos, 50 + line, 6,"fork %d (%d)", read_bytes(env->memory, save + 1, 2),
								save + read_bytes(env->memory, save + 1, 2));
		line++;
	}
	else if (env->memory[save] == 0x0f)
	{
		mvwprintw(env->infos, 50 + line, 6,"lfork %d (%d)", read_bytes(env->memory, save + 1, 2),
								save + read_bytes(env->memory, save + 1, 2));
		line++;
	}
	else
	{
		if (env->champ[j].op.name != NULL)
			mvwprintw(env->infos, 50 + line, 6,"%s", env->champ[j].op.name);
		while (env->champ[j].op.param[i])
			mvwprintw(env->infos, 50 + line, 6," %s", env->champ[j].op.param[i++]);
		if (env->memory[save] == 0x01
				&& (ft_strcmp(env->champ[j].op.param[0], "-1") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-2") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-3") == 0
					|| ft_strcmp(env->champ[j].op.param[0], "-4") == 0))
			mvwprintw(env->infos, 50 + line, 6,"Player %d (%s) is said to be alive",
						UINT_MAX - ft_atoi(env->champ[j].op.param[0]) + 1,
						env->live[UINT_MAX - ft_atoi(env->champ[j].op.param[0])].header.prog_name);
		else if (env->memory[save] == 0x0b && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[1]) + ft_atoi(env->champ[j].op.param[2]);
			mvwprintw(env->infos, 50 + line, 6,"       | -> store to %s + %s = %d",
						env->champ[j].op.param[1], env->champ[j].op.param[2],
						tmp);
		}
		else if (env->memory[save] == 0x0a && env->champ[j].check_args == 1)
		{
			tmp = ft_atoi(env->champ[j].op.param[0]) + ft_atoi(env->champ[j].op.param[1]);
			mvwprintw(env->infos, 50 + line, 6,"       | -> load from %s + %s = %d",
						env->champ[j].op.param[0], env->champ[j].op.param[1],
						tmp);
		}
		while (env->champ[j].op.param[i])
			free(env->champ[j].op.param[i++]);
	}
}