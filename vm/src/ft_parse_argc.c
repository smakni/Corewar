/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:31:42 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/24 14:35:01 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	ft_check_duplicate(t_player *tmp, unsigned int nb)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < nb)
	{
		j = 0;
		if (tmp[i].id > nb)
			return (print_error("error, player number too high\n"));
		while (j < nb)
		{
			if (j != i && tmp[i].id == tmp[j].id && tmp[i].id != 0)
				return (print_error("error\n"));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static void	ft_sort_argc2(t_env *env, t_player *tmp, unsigned i, unsigned j)
{
	j = 0;
	while (j < env->nb_process)
	{
		if (tmp[j].id == 0)
		{
			tmp[j].id = i;
			env->player[i - 1] = tmp[j];
			break ;
		}
		j++;
	}
}

static int	ft_sort_argc(t_env *env, t_player *tmp)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if (ft_check_duplicate(tmp, env->nb_process) == FAIL)
		return (FAIL);
	while (++i < env->nb_process + 1)
	{
		j = -1;
		while (++j < env->nb_process)
			if (tmp[j].id == i)
			{
				env->player[i - 1] = tmp[j];
				break ;
			}
		if (j == env->nb_process)
			ft_sort_argc2(env, tmp, i, j);
	}
	return (SUCCESS);
}

static int	ft_options(int argc, char **argv, t_env *env, int i)
{
	if (ft_strequ(argv[i], "-visu"))
		env->option = 1;
	else if (ft_strequ(argv[i], "-svisu"))
		env->option = 2;
	else if (ft_strequ(argv[i], "-goback"))
		env->goback = 1;
	else if (ft_strequ(argv[i], "-dump"))
	{
		if (i + 1 < argc && ft_isdigit(argv[i + 1][0]) != 0)
			env->dump = ft_atoi(argv[++i]);
		else
			return (print_error("error\n"));
		env->option = 3;
	}
	return (SUCCESS);
}

int			ft_parse_argc(int argc, char **argv, t_env *env)
{
	int			i;
	t_player	tmp[4];

	ft_bzero(tmp, 4 * sizeof(t_player));
	i = -1;
	while (++i < argc)
	{
		if (ft_strstr(argv[i], ".cor"))
		{
			ft_memcpy(tmp[env->nb_process].header.prog_name,
				argv[i], PROG_NAME_LENGTH + 1);
			env->nb_process++;
		}
		else if (ft_strequ(argv[i], "-n"))
		{
			if (i + 2 < argc && ft_isdigit(argv[i + 1][0]) != 0)
				tmp[env->nb_process].id = ft_atoi(argv[++i]);
			else
				return (print_error("error\n"));
		}
		else if (ft_options(argc, argv, env, i) == FAIL)
			return (FAIL);
	}
	return (ft_sort_argc(env, tmp));
}
