/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 12:35:29 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/29 12:44:36 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	save_dir_param(t_env *env, int j, int value, int index)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa(value);
	if (!(env->process[j].op.param[index] = ft_strjoin("%", tmp)))
	{
		ft_dprintf(2, "{red}Fail to malloc something.{reset}\n");
		exit(EXIT_FAILURE);
	}
	ft_strdel(&tmp);
	env->process[j].op.param[3] = NULL;
}

void	save_ind_param(t_env *env, int j, int value, int index)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa(value);
	if (!(env->process[j].op.param[index] = ft_strjoin(
			env->process[j].op.param[index], tmp)))
	{
		ft_dprintf(2, "{red}Fail to malloc something.{reset}\n");
		exit(EXIT_FAILURE);
	}
	ft_strdel(&tmp);
	env->process[j].op.param[3] = NULL;
}

void	save_reg_param(t_env *env, int j, int value, int index)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa(value);
	if (!(env->process[j].op.param[index] = ft_strjoin("r", tmp)))
	{
		ft_dprintf(2, "{red}Fail to malloc something.{reset}\n");
		exit(EXIT_FAILURE);
	}
	ft_strdel(&tmp);
	env->process[j].op.param[3] = NULL;
}
