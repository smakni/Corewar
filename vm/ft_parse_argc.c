/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:31:42 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_options2(t_env *env, char **argv, int *i)
{
	if (ft_strequ(argv[*i], "-a"))
		env->aff = 1;
	else
	{
		env->err_code = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

static int	ft_options(int argc, char **argv, t_env *env, int *i)
{
	if (ft_strequ(argv[*i], "-visu"))
		env->option = 1;
	else if (ft_strequ(argv[*i], "-svisu"))
		env->option = 2;
	else if (ft_strequ(argv[*i], "-v"))
		env->verb = 1;
	else if (ft_strequ(argv[*i], "-goback"))
		env->goback = 1;
	else if (ft_strequ(argv[*i], "-dump"))
	{
		if (*i + 1 < argc && ft_str_is_numeric(argv[*i + 1]) != 0)
			env->dump = ft_atoi(argv[++*i]);
		else
			return (print_error("ERROR: Invalid option `-dump`"));
		env->option = 3;
	}
	else
		return (ft_options2(env, argv, i));
	return (SUCCESS);
}

static int	copy_player_name(t_env *env, t_player *tmp, const char *argv)
{
	ft_memcpy(tmp[env->nb_process].header.prog_name,
		argv, PROG_NAME_LENGTH + 1);
	env->nb_process++;
	env->nb_player++;
	if (env->nb_process > MAX_PLAYERS)
		return (print_error("ERROR: Too many players received"));
	return (SUCCESS);
}

static int	valid_file_ext(const char *argv)
{
	char	*ptr;

	ptr = ft_strstr(argv, CHAMP_EXTENSION);
	if (!ptr)
		return (FAIL);
	if (ft_strlen(ptr) != 4)
		return (FAIL);
	return (SUCCESS);
}

int			ft_parse_argc(int argc, char **argv, t_env *env)
{
	int			i;
	t_player	tmp[MAX_PLAYERS];

	ft_bzero(tmp, MAX_PLAYERS * sizeof(t_player));
	i = 0;
	while (++i < argc)
	{
		if (valid_file_ext(argv[i]))
		{
			if (copy_player_name(env, tmp, argv[i]) == FAIL)
				return (FAIL);
		}
		else if (ft_strequ(argv[i], "-n"))
		{
			if (i + 2 < argc && ft_isdigit(argv[i + 1][0]) != 0
					&& argv[i + 1][0] != '0' && ft_strlen(argv[i + 1]) == 1)
				tmp[env->nb_process].id = ft_atoi(argv[++i]);
			else
				return (print_error("ERROR: wrong arg received"));
		}
		else if (ft_options(argc, argv, env, &i) == FAIL)
			return (FAIL);
	}
	return (ft_sort_argc(env, tmp));
}
