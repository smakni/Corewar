/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_argc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:28:38 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_check_duplicate(t_player *tmp, unsigned int nb)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < nb)
	{
		j = 0;
		if (tmp[i].id > nb)
			return (print_error("ERROR: wrong player number"));
		while (j < nb)
		{
			if (j != i && tmp[i].id == tmp[j].id && tmp[i].id != 0)
				return (print_error("ERROR"));
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

int			ft_sort_argc(t_env *env, t_player *tmp)
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
