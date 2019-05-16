/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:54:12 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/16 17:32:20 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	ft_display_commands(void)
{
	ft_printf("Commands and options for running the vm displayed here\n");
	return (-1);
}

static void	ft_print_memory(t_env *env)
{
	int		i;

	i = 0;
/*	while (i < 4096)
	{
		ft_printf("%.2x ", env->memory[i]);
		i++;
		if (i % 64 == 0)
			ft_putendl("");
	}*/
	i = 0;
	while (i < env->nb_champs)
	{
		ft_printf("player's name : %s | player's nb : %d\n", env->champ[i].name, env->champ[i].player_nb);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		i;

	ft_bzero(&env, sizeof(t_env));
	if (argc > 1)
		ft_parse_argc(argc, argv, &env);
	else
		return (ft_display_commands());
	ft_print_memory(&env);
	return (0);
}
