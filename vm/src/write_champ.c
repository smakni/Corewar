/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/08 14:42:43 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		init_process(t_env *env, unsigned int j, int *id, int i)
{
	ft_bzero(&(env->process[j]), sizeof(t_process));
	env->player[j].last_live = 0;
	env->process[j].id = *id;
	env->process[j].nb = j;
	env->process[j].r[1] = (*id)--;
	env->process[j].pc = i;
	env->process[j].live = -1;
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

static int		write_content(t_env *env, unsigned int j, int *id,
					unsigned int i)
{
	unsigned char	line[MAX_SIZE + 1];
	unsigned int	ret;

	ret = read(env->fd, &line, MAX_SIZE);
	env->player[j].header.prog_size = read_bytes(line, 0x8a, 2);
	if (check_champ(env, j, ret, line) == FAIL)
		return (FAIL);
	cpy_champ_info(env, j, i, line);
	init_process(env, j, id, i);
	return (SUCCESS);
}

int				write_champ(t_env *env)
{
	unsigned		i;
	unsigned		j;
	int				id;

	i = 0;
	j = 0;
	id = 0xffffffff;
	if (env->option == 1 || env->option == 2)
		first_visu(env);
	while (j < env->nb_process)
	{
		if (!(safe_open(env->player[j].header.prog_name, env, O_RDONLY)))
			return (FAIL);
		if (write_content(env, j, &id, i) == FAIL)
			return (FAIL);
		if (close(env->fd) < 0)
			return (FAIL);
		if (env->option == 1 || env->option == 2)
			write_champ_visu(env, j);
		i += MEM_SIZE / env->nb_process;
		j++;
		env->living_proc++;
	}
	env->winner = env->nb_process;
	return (SUCCESS);
}
