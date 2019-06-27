/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/27 11:27:53 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	clean_quit(t_env *env, const int ret)
{
	ft_memdel((void *)&env->process);
	return (ret);
}

static int	ft_display_commands(void)
{
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	ft_printf("	-Maximum number of champions : 4\n");
	return (-1);
}

void		ft_print_memory(t_env *env)
{
	int	i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < 4096)
	{
		ft_printf("%.2x ", env->memory[i]);
		i++;
		if (i % 64 == 0)
		{
			if (i != 4096)
				ft_printf("\n%#.4x : ", i);
			else
				ft_putendl("");
		}
	}
}

int			check_last_live(t_env *env)
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
		//		env->player[i].header.prog_name, env->player[i].last_live);
		if (env->player[i].last_live > last_live)
		{
			//ft_printf("SAVE");
			//ft_printf("[%s]live = %d\n",
			//	env->player[i].header.prog_name, env->player[i].last_live);
			last_live = env->player[i].last_live;
			save = i;
		}
		i++;
	}
	if (env->option == 1 || env->option == 2)
	{
		if (env->option == 1)
		{
			mvwprintw(env->state, 0, 0, "**Game Over**");
			mvwprintw(env->infos, 46, 0, "WINNER :");
			wattron(env->infos, COLOR_PAIR(4 + save));
			mvwprintw(env->infos, 46, 9, "%s", env->player[save].header.prog_name);
			wattroff(env->infos, COLOR_PAIR(4 + save));
			wrefresh(env->infos);
			wrefresh(env->state);
		}
		timeout(-1);
		while (1)
			if (getch())
			{
				i = 0;
				while (i < GO_BACK && i < env->cycle_index)
				{
					delwin(env->trace[i]);
					if (env->option == 1)
						delwin(env->traceinfos[i]);
					if (env->option == 1 && env->verb == 1)
						delwin(env->traceverbos[i]);
					i++;
				}
				delwin(env->mem);
				delwin(env->around_memory);
				if (env->option == 1)
				{
					delwin(env->state);
					delwin(env->commands);
					delwin(env->infos);
					delwin(env->around_infos);
					if (env->verb == 1)
					delwin(env->verbos);
					delwin(env->around_verbos);
				}
				endwin();
				break ;
			}
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n", save + 1, env->player[save].header.prog_name);
	return (save);
}

static void	init_op_tab(t_env *env)
{
	env->op_cycles[0] = 1;
	env->op_cycles[1] = 10;
	env->op_cycles[2] = 5;
	env->op_cycles[3] = 5;
	env->op_cycles[4] = 10;
	env->op_cycles[5] = 10;
	env->op_cycles[6] = 6;
	env->op_cycles[7] = 6;
	env->op_cycles[8] = 6;
	env->op_cycles[9] = 20;
	env->op_cycles[10] = 25;
	env->op_cycles[11] = 25;
	env->op_cycles[12] = 800;
	env->op_cycles[13] = 10;
	env->op_cycles[14] = 50;
	env->op_cycles[15] = 1000;
	env->op_cycles[16] = 2;
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		init_op_tab(&env);
		env.nb_realloc = 1;
		if (!(env.process = ft_memalloc(sizeof(t_process) * ARR_SIZE)))
			return (-1);
		if (ft_parse_argc(argc, argv, &env) == FAIL)
			return (clean_quit(&env, -1));
		if (write_champ(&env) == FAIL)
			return (clean_quit(&env, -1));
		if (read_memory(&env) == FAIL)
			return (clean_quit(&env, -1));
		check_last_live(&env);
		return (clean_quit(&env, 0));
	}
	return (ft_display_commands());
}
