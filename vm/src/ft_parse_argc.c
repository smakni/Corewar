/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:31:42 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/23 20:07:11 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int ft_check_duplicate(t_champ *tmp, unsigned int nb)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < nb)
	{
		j = 0;
		if (tmp[i].player_nb > nb)
		{
			ft_printf("error, player number too high\n", tmp[i].player_nb);
			return (FAIL);
		}
		while (j < nb)
		{
			if (j != i && tmp[i].player_nb == tmp[j].player_nb && tmp[i].player_nb != 0)
			{
				ft_printf("error\n");
				return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int ft_sort_argc(t_env *env, t_champ *tmp)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if (ft_check_duplicate(tmp, env->nb_champs) == FAIL)
		return (FAIL);
	while (++i < env->nb_champs + 1)
	{
		j = -1;
		while (++j < env->nb_champs)
			if (tmp[j].player_nb == i)
			{
				env->champ[i - 1] = tmp[j];
				break;
			}
		if (j == env->nb_champs)
		{
			j = -1;
			while (++j < env->nb_champs)
				if (tmp[j].player_nb == 0)
				{
					tmp[j].player_nb = i;
					env->champ[i - 1] = tmp[j];
					break;
				}
		}
	}
	return (SUCCESS);
}

int		ft_parse_argc(int argc, char **argv, t_env *env)
{
	int i;
	t_champ tmp[4];

	ft_bzero(tmp, 4 * sizeof(t_champ));
	i = 0;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-n"))
		{
			if (i + 2 < argc && ft_isdigit(argv[i + 1][0]) != 0)
				tmp[env->nb_champs].player_nb = ft_atoi(argv[++i]);
			else
			{
				ft_printf("error\n");
				return (FAIL);
			}
		}
		else if (ft_strequ(argv[i], "-visu"))
			env->visu = 1;
		else if (ft_strstr(argv[i], ".cor"))
		{
			ft_memcpy(tmp[env->nb_champs].header.prog_name,
					  argv[i], PROG_NAME_LENGTH + 1);
			env->nb_champs++;
		}
		i++;
	}
	ft_sort_argc(env, tmp);
	return (SUCCESS);
}
/*

int		ft_parse_argc(int argc, char **argv, t_env *env)
{
	(void)argc;
	argv++;
	while (*argv)
	{
		ft_memcpy(env->champ[env->nb_champs].header.prog_name,
					*argv, PROG_NAME_LENGTH + 1);
		env->nb_champs++;
		argv++;
	}
	if (env->nb_champs <= 0 ||env->nb_champs > 4)
		return (FAIL);
	return (SUCCESS);
}*/