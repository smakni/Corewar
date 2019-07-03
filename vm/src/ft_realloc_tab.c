/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:27:15 by sabri             #+#    #+#             */
/*   Updated: 2019/07/03 15:32:51 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int	ft_realloc_tab(t_env *env)
{
	t_process		*tmp;
	unsigned int	i;

	env->capacity *= 2;
	i = 0;
	if (!(tmp = ft_memalloc(sizeof(t_player) * (env->capacity))))
	{
		ft_memdel((void *)&env->process);
		return (-1);
	}
	while (i < env->nb_process)
	{
		tmp[i] = env->process[i];
		i++;
	}
	free(env->process);
	env->process = tmp;
	return (0);
}