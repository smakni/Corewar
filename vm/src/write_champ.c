/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/02 20:08:06 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int		check_header_cor_file(t_env *env, unsigned int j)
{
	ft_dprintf(2, "Error: File %s has an invalid header\n",
			env->player[j].header.prog_name);
	return (FAIL);
}

static int		check_champ(t_env *env, unsigned int j, unsigned int ret,
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

static void		init_process(t_env *env, unsigned int j, int *id, int i)
{
	ft_bzero(&(env->process[j].op), sizeof(t_op));
	env->player[j].last_live = 0;
	env->process[j].last_live = 0;
	env->process[j].id = *id;
	env->process[j].nb = j;
	env->process[j].r[1] = (*id)--;
	env->process[j].pc = i;
	env->process[j].cycles = check_cycles(env, j);
	env->process[j].carry = 0;
	env->process[j].live = -1;
	env->process[j].nb_live = 0;
}

static void		cpy_champ_info(t_env *env, unsigned int j, int i,
					unsigned char line[MAX_SIZE + 1])
{
	ft_memcpy(env->player[j].header.prog_name,
				&line[4], PROG_NAME_LENGTH);
	ft_memcpy(env->player[j].header.comment,
				&line[0x8c], COMMENT_LENGTH - 10);
	ft_memcpy(&env->memory[i], &line[0x890],
				env->player[j].header.prog_size);
}

int				write_champ(t_env *env)
{
	unsigned		i;
	unsigned		j;
	unsigned		ret;
	int				id;
	unsigned char	line[MAX_SIZE + 1];

	i = 0;
	j = 0;
	id = 0xffffffff;
	if (env->option == 1 || env->option == 2)
		first_visu(env);
	while (j < env->nb_process)
	{
		if (!(safe_open(env->player[j].header.prog_name, env, O_RDONLY)))
			return (FAIL);
		ret = read(env->fd, &line, MAX_SIZE);
		env->player[j].header.prog_size = read_bytes(line, 0x8a, 2);
		if (check_champ(env, j, ret, line) == FAIL)
			return (FAIL);
		cpy_champ_info(env, j, i, line);
		init_process(env, j, &id, i);
		if (close(env->fd) < 0)
			return (FAIL);
		if (env->option == 1 || env->option == 2)
			write_champ_visu(env, j);
		i += MEM_SIZE / env->nb_process;
		j++;
	}
	return (SUCCESS);
}
