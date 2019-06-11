/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:06:24 by sabri             #+#    #+#             */
/*   Updated: 2019/05/29 14:14:14 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void del_process_visu(t_env *env)
{
	unsigned	j;
	unsigned	x;
	unsigned	y;
	int			color;

	j = 0;
	while (j < env->nb_champs)
	{
		if (env->champ[j].nb_live == 0)
		{
			x = env->champ[j].pc % 64 * 3;
			y = env->champ[j].pc / 64;
			remove_bold(env, j);
			color = mvwinch(env->mem, y, x) & A_COLOR;
			if (color == COLOR_PAIR(12))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 1, NULL);
			else if (color == COLOR_PAIR(8))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 4, NULL);
			else if (color == COLOR_PAIR(9))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 5, NULL);
			else if (color == COLOR_PAIR(10))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 6, NULL);
			else if (color == COLOR_PAIR(11))
				mvwchgat(env->mem, y, x, 2, A_NORMAL, 7, NULL);
		}
		j++;
	}
}
int del_process(t_env *env)
{
	t_champ		*tmp;
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	if (!(tmp = (t_champ *)malloc(sizeof(t_champ) * (ARR_SIZE * env->nb_realloc))))
		return (-1);
	if (env->visu == 1)
		del_process_visu(env);
	while (j < env->nb_champs)
	{
		if (env->champ[j].nb_live > 0)
		{
			tmp[i] = env->champ[j];
			tmp[i++].nb_live = 0;
		}
		j++;
	}
	ft_memdel((void *)&env->champ);
	env->champ = tmp;
	env->nb_champs = i;
	return (0);
}
