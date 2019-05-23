/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/23 20:09:26 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	clean_quit(t_env *env, const int ret)
{
	ft_memdel((void*)&env->champ);
	return (ret);
}

static int	ft_display_commands(void)
{
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	ft_printf("	-Maximum number of champions : 4\n");
	return (-1);
}

void	ft_print_memory(t_env *env)
{
	int		i;
	int	flag = 0;

	ft_printf("{CLEAR}");
	i = 0;
	ft_putendl("");
	while (i < 4096)
	{
		int j = 0;
		while (j < env->nb_champs)
		{
			if (env->champ[j].pc == (unsigned)i)
			{
				flag = 1;
				if (env->champ[j].player_nb == 0xffffffff)
					ft_printf("{BG_GREEN}");
				else if (env->champ[j].player_nb == 0xfffffffe)
					ft_printf("{BG_BLUE}");
				else if (env->champ[j].player_nb == 0xfffffffd)
					ft_printf("{BG_RED}");
				else if (env->champ[j].player_nb == 0xfffffffc)
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
	return ;
	i = 0;
	while (i < env->nb_champs)
	{
		ft_printf("player's name : %s [r1 = %x] | nb_lives = %d\n",
		env->champ[i].header.prog_name, env->champ[i].r[1], env->champ[i].last_live);
		i++;
	}
}

int 		check_last_live(t_env *env)
{
	int i;
	int save;

	i = 0;
	save = 0;
	while (i < env->nb_champs)
	{
		if (env->champ[i].last_live > save)
			save = i;
		i++;
	}
	ft_printf(">>>>>winner_is_%s>>>>LIVE>>%d\n", env->champ[save].header.prog_name, env->champ_live[save]);
	return (save);
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		env.nb_realloc = 1;
		if (!(env.champ = (t_champ *)malloc(sizeof(t_champ) * ARR_SIZE)))
			return (-1);
		if (ft_parse_argc(argc, argv, &env) == FAIL)
			return (clean_quit(&env, FAIL));
	}
	else
		return (ft_display_commands());
	write_champ(&env);
	read_memory(&env);
	check_last_live(&env);
	ft_print_memory(&env);
	return (0);
}
