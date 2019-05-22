/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:06:24 by sabri             #+#    #+#             */
/*   Updated: 2019/05/22 13:42:21 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		del_process(t_env *env)
{
	t_champ *tmp;
	int 	i;
	int		j;

	i = 0;
	j = 0;
	if (!(tmp = (t_champ *)malloc(sizeof(t_champ)
							* (ARR_SIZE * env->nb_realloc))))
		return (-1);
	while (j < env->nb_champs)
	{
		if (env->champ[j].last_live > -1)
		{
			ft_printf("AVANT\n");
			tmp[i] = env->champ[j]; // acces a une valeur free -> error
			ft_printf("APRES\n");
			i++;
		}
		j++;
	}

	ft_memdel((void *)&env->champ);
	env->champ = tmp;
	env->nb_champs = i;
	return (0);
}