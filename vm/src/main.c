/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/06 15:38:24 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int clean_quit(t_env *env, const int ret)
{
	ft_memdel((void *)&env->champ);
	return (ret);
}

static int ft_display_commands(void)
{
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	ft_printf("	-Maximum number of champions : 4\n");
	return (-1);
}

void ft_print_memory(t_env *env)
{
	int	i;
	int flag = 0;

	ft_printf("{CLEAR}");
	i = 0;
	ft_putendl("");
	i = 0;/*
	while ((unsigned)i < env->nb_champs)
	{
		ft_printf("id : %s [%x] | live_call = {%d} | last_lives = {%d}\n",
		env->champ[i].header.prog_name, env->champ[i].r[1], env->champ[i].nb_live, env->champ[i].last_live);
		ft_printf("PROCESS[%d]<<PC[%d]\n", i, env->champ[i].pc);
		ft_printf("OP{%.2x}", env->memory[env->champ[i].pc]);
		ft_printf("[%2d]\n", env->champ[i].cycles);
		i++;
	}*/
	i = 0;
	ft_printf("NB_PROCESS>>[%3d]\n", env->nb_champs);
	ft_printf("CTD>>>>>>>>>>>>>>[%d]<<<<<<<<<<<<<<[%d]\n", env->cycle_index, env->cycle_to_die);
	while (i < 4096)
	{
		unsigned j = 0;
		while (j < env->nb_champs)
		{
			if (env->champ[j].pc == i)
			{
				flag = 1;
				if (env->champ[j].id == 0xffffffff)
					ft_printf("{BG_GREEN}");
				else if (env->champ[j].id == 0xfffffffe)
					ft_printf("{BG_BLUE}");
				else if (env->champ[j].id == 0xfffffffd)
					ft_printf("{BG_RED}");
				else if (env->champ[j].id == 0xfffffffc)
					ft_printf("{BG_CYAN}");
			}
			j++;
		}
		ft_printf("%.2x", env->memory[i]);
		if (flag == 1)
			ft_printf("{reset}");
		ft_printf(" ");
		i++;
		if (i % 64 == 0)
			ft_putendl("");
	}
}

int check_last_live(t_env *env)
{
	int	i;
	int	save;
	int	last_live;

	i = 0;
	save = 0;
	last_live = -1;
	while (i < MAX_PLAYERS)
	{
		//ft_printf("[%s]live = %d\n",
		//		env->live[i].header.prog_name, env->live[i].last_live);
		if (env->live[i].last_live > last_live)
		{	
			//ft_printf("SAVE");
			//ft_printf("[%s]live = %d\n",
			//	env->live[i].header.prog_name, env->live[i].last_live);
			last_live = env->live[i].last_live;
			save = i;
		}
		i++;
	}
	if (env->visu == 1)
	{
		mvwprintw(env->infos, 50, 6, ">>>>>winner_is_%s>>>>LIVE>>%d\n", env->live[save].header.prog_name, env->live[save].last_live);
		wrefresh(env->infos);
		while (1)
			if (getch() == ' ')
			{
				delwin(env->mem);
				delwin(env->infos);
				delwin(env->around_infos);
				delwin(env->around_memory);
				endwin();
            	break ;
			}
	}
	else
		ft_printf(">>>>>winner_is_%s>>>>LIVE>>%d\n", env->live[save].header.prog_name, env->live[save].last_live);
	return (save);
}

int main(int argc, char **argv)
{
	t_env env;

	if (argc > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		env.nb_realloc = 1;
		if (!(env.champ = (t_champ *)malloc(sizeof(t_champ) * ARR_SIZE)))
			return (-1);
		if (ft_parse_argc(argc, argv, &env) == FAIL)
			return (clean_quit(&env, -1));
	}
	else
		return (ft_display_commands());
	if (env.visu == 1)
		first_visu(&env);
	if (write_champ(&env) == FAIL)
		return (clean_quit(&env, -1));
	if (read_memory(&env) == FAIL)
		return (clean_quit(&env, -1));
	check_last_live(&env);
	//ft_print_memory(&env);
	return (0);
}
