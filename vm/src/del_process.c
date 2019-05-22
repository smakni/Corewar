/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:06:24 by sabri             #+#    #+#             */
/*   Updated: 2019/05/22 01:39:28 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		del_process(t_env *env)
{
	t_champ *tmp;
	int 	i;
	int		j;
	int 	save;

	i = 0;
	j = 0;
	save = env->nb_champs;
	if (!(tmp = (t_champ *)malloc(sizeof(t_champ)
							* (ARR_SIZE * env->nb_realloc))))
		return (-1);
	while (j < save)
	{
		if (env->champ[j].last_live == -1)
		{
			tmp[i] = env->champ[j];
			i++;
		}
		j++;
		env->nb_champs--;
	}
	ft_memdel((void *)&env->champ);
	env->champ = tmp;
	return (0);
}