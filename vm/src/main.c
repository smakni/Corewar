/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/04 11:07:05 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	ft_display_usage(void)
{
	ft_dprintf(2, "./corewar [-dump nbr_cycles] [[-n number] champion1.cor]");
	ft_dprintf(2, " ...\n\t-Maximum number of champions : 4\n");
	ft_dprintf(2, "Options :\n");
	ft_dprintf(2, "\tNcurses visualizer : -visu (without infos : -svisu)\n");
	ft_dprintf(2, "\tMove through cycles in the visualizer : -visu -goback\n");
	ft_dprintf(2, "\tPrint verbos (works with visualizer and without it)");
	ft_dprintf(2, " : -v\n");
	return (-1);
}

static int	clean_quit(t_env *env, const int ret)
{
	if (env->err_code > 1)
	{
		ft_dprintf(2, "{red}%s.{reset}\n", env->err_msg);
		if (env->err_code == 2)
			return (ret);
	}
	else if (env->err_code == 1)
	{
		ft_memdel((void *)&env->process);
		return (ft_display_usage());
	}
	ft_memdel((void *)&env->process);
	return (ret);
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

static void	init_op_fun(t_env *env)
{
	env->op_fun[0] = op_live;
	env->op_fun[1] = op_ld;
	env->op_fun[2] = op_st;
	env->op_fun[3] = op_add;
	env->op_fun[4] = op_sub;
	env->op_fun[5] = op_and;
	env->op_fun[6] = op_or;
	env->op_fun[7] = op_xor;
	env->op_fun[8] = op_zjmp;
	env->op_fun[9] = op_ldi;
	env->op_fun[10] = op_sti;
	env->op_fun[11] = op_fork;
	env->op_fun[12] = op_lld;
	env->op_fun[13] = op_lldi;
	env->op_fun[14] = op_lfork;
	env->op_fun[15] = op_aff;
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		if (ft_check_args_validity(argv, &env) == FAIL)
			return (clean_quit(&env, -1));
		init_op_tab(&env);
		init_op_fun(&env);
		env.capacity = ARR_SIZE;
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
	return (ft_display_usage());
}
