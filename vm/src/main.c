/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/22 13:21:37 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	ft_display_commands(void)
{
	ft_printf("Commands and options for running the vm displayed here\n");
	return (-1);
}

void	ft_print_memory(t_env *env)
{
	int		i;

	i = 0;
	while (i < 4096)
	{
		ft_printf("%.2x ", env->memory[i]);
		i++;
		if (i % 64 == 0)
			ft_putendl("");
	}
	i = 0;
	while (i < 4)
	{
		ft_printf("player's name : %s [r1 = %x] | nb_lives = %d\n",
		env->champ[i].header.prog_name, env->champ[i].r[1], env->champ_live[i]);
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
	ft_printf(">>>>>winner_is_%s>>>>LIVE>>%d\n", env->champ[save].header.prog_name, env->champ_live[0]);
	return (save);
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		if (!(env.champ = (t_champ *)malloc(sizeof(t_champ) * ARR_SIZE)))
			return (-1);
		ft_parse_argc(argc, argv, &env);
	}
	else
		return (ft_display_commands());
	write_champ(&env);
	read_memory(&env);
	//check_last_live(&env);
	//ft_print_memory(&env);
	return (0);
}
