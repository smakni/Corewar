/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/05/23 19:14:32 by sabri            ###   ########.fr       */
=======
/*   Updated: 2019/05/23 18:54:07 by jergauth         ###   ########.fr       */
>>>>>>> 7c9c03cc0b9ca74795e4fb56a1fc690e250aa2b2
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	write_champ(t_env *env)
{
	int i;
	int j;
	int fd;
	int	id;
	unsigned char line[MAX_CHAMP_CODE_SIZE + 1];

	i = 0;
	j = 0;
	id = 0xffffffff;
	while (j < env->nb_champs)
	{
		fd = open(env->champ[j].header.prog_name, O_RDONLY);
		read(fd, &line, MAX_CHAMP_CODE_SIZE);
		ft_memcpy(env->champ[j].header.prog_name, &line[4], PROG_NAME_LENGTH);
		ft_memcpy(env->champ[j].header.comment,
					&line[0x8c], COMMENT_LENGTH - 10);
		env->champ[j].header.prog_size = read_multi_bytes(line, 0x8b, 2);
		if (env->champ[j].header.prog_size > CHAMP_MAX_SIZE)
		{
			ft_printf("SIZE_ERROR\n");
			exit (0);
		}
		ft_memcpy(&env->memory[i], &line[0x890],
					env->champ[j].header.prog_size);
		env->champ[j].player_nb = id;
		env->champ[j].r[1] = id--;
		env->champ[j].pc = i;
		env->champ[j].cycles = check_cycles(env, j);
<<<<<<< HEAD
	//	ft_printf("cycles = %i\n", env->champ[j].cycles);
=======
>>>>>>> 7c9c03cc0b9ca74795e4fb56a1fc690e250aa2b2
		env->champ[j].last_live = -1; 
		close(fd);
		i += 4096 / env->nb_champs;
		j++;
	}
}
