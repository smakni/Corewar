/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_champ_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 09:55:24 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	check_header_cor_file(t_env *env, unsigned int j)
{
	ft_dprintf(2, "Error: File %s has an invalid header\n",
			env->player[j].header.prog_name);
	return (FAIL);
}

int			check_champ(t_env *env, unsigned int j, unsigned int ret,
					unsigned char line[MAX_SIZE + 1])
{
	if (line[0] != 0x00 || line[1] != 0xea
			|| line[2] != 0x83 || line[3] != 0xf3)
		return (check_header_cor_file(env, j));
	if (ret - 0x890 != env->player[j].header.prog_size)
	{
		ft_dprintf(2,
			"Error: File %s's code size differ from what its header says\n",
				env->player[j].header.prog_name);
		return (FAIL);
	}
	else if (env->player[j].header.prog_size > CHAMP_MAX_SIZE)
	{
		ft_dprintf(2,
			"Error: File %s has too large a code (%d bytes > %d bytes)\n",
				env->player[j].header.prog_name,
					env->player[j].header.prog_size, CHAMP_MAX_SIZE);
		return (FAIL);
	}
	else if (env->player[j].header.prog_size == 0)
	{
		ft_dprintf(2, "Error: File %s is too small to be a champion\n",
					env->player[j].header.prog_name);
		return (FAIL);
	}
	return (SUCCESS);
}
