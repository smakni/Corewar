/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/05/16 19:41:58 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	write_champ(t_env *env, char *argv)
{
	int i;
	int fd;
	char line[4096];

	i = 0;
	while (i < env->nb_champs)
	{
		if (env->champ[i].player_nb == 1)
		{
			fd = open(argv, O_RDONLY);
			read(fd, &line, 4096);
			ft_memcpy(env->memory, &line[0x890], line[0x8b]);
		}
		i++;
	}
}