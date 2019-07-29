/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:06:57 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
