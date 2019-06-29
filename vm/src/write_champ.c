/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:58:56 by smakni            #+#    #+#             */
/*   Updated: 2019/06/29 12:25:49 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void		check_last(t_env *env, unsigned j)
{
	if (j == env->nb_process - 1)
	{
		if (env->option == 1)
		{
			if (mvwprintw(env->state, 0, 0, "** PAUSED ** ") == ERR)
				exit_clean(env);
			print_infos(env);
			protect_wrefresh(env, env->state);
			env->traceinfos[env->cycle_index] = protect_dupwin(env, env->infos);
		}
		protect_wrefresh(env, env->mem);
		if (!(env->trace[env->cycle_index] = dupwin(env->mem)))
			exit_clean(env);
	}
}

static void		write_champ_body(t_env *env, unsigned y, unsigned x, unsigned j)
{
	unsigned	k;
	unsigned	start;

	k = 1;
	start = 4096 * j / env->nb_process;
	if (wattron(env->mem, COLOR_PAIR(env->process[j].color)) == ERR)
		exit_clean(env);
	while (k < env->player[j].header.prog_size)
	{
		if (mvwprintw(env->mem, y, x, "%.2x", env->memory[start + k]) == ERR)
			exit_clean(env);
		x += 3;
		if (x >= 192)
		{
			x -= 192;
			y++;
		}
		k++;
	}
	if (wattroff(env->mem, COLOR_PAIR(4 + j)) == ERR)
		exit_clean(env);
}

static void		write_champ_visu(t_env *env, unsigned j)
{
	unsigned	x;
	unsigned	y;

	env->process[j].color = 4 + j;
	x = 4096 * j / env->nb_process % 64 * 3;
	y = 4096 / env->nb_process / 64 * j;
	if (wattron(env->mem, COLOR_PAIR(env->process[j].color + 4)) == ERR)
		exit_clean(env);
	if (mvwprintw(env->mem, y, x, "%.2x", env->memory[4096 * j / env->nb_process]) == ERR)
		exit_clean(env);
	x += 3;
	if (x >= 192)
	{
		x -= 192;
		y++;
	}
	if (wattroff(env->mem, COLOR_PAIR(env->process[j].color + 4)) == ERR)
		exit_clean(env);
	write_champ_body(env, y, x, j);
	check_last(env, j);
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
		if (line[0] != 0x00 || line[1] != 0xea || line[2] != 0x83 || line[3] != 0xf3)
		{
			ft_dprintf(2, "Error: File %s has an invalid header\n", env->player[j].header.prog_name);
			return (FAIL);
		}
		env->player[j].header.prog_size = read_bytes(line, 0x8a, 2);
		if (ret - 0x890 != env->player[j].header.prog_size)
		{
			ft_dprintf(2, "Error: File %s has a code size that differ from what its header says\n", env->player[j].header.prog_name);
			return (FAIL);
		}
		else if (env->player[j].header.prog_size > CHAMP_MAX_SIZE)
		{
			ft_dprintf(2, "Error: File %s has too large a code (%d bytes > %d bytes)\n",
						env->player[j].header.prog_name, env->player[j].header.prog_size,
						CHAMP_MAX_SIZE);
			return (FAIL);
		}
		else if (env->player[j].header.prog_size == 0)
		{
			ft_dprintf(2, "Error: File %s is too small to be a champion\n",
						env->player[j].header.prog_name);
			return (FAIL);
		}
		ft_memcpy(env->player[j].header.prog_name,
					&line[4], PROG_NAME_LENGTH);
		ft_memcpy(env->player[j].header.comment,
					&line[0x8c], COMMENT_LENGTH - 10);
		ft_memcpy(&env->memory[i], &line[0x890],
					env->player[j].header.prog_size);
		ft_bzero(&(env->process[j].op), sizeof(t_op));
		env->player[j].last_live = 0;
		env->process[j].last_live = 0;
		env->process[j].id = id;
		env->process[j].nb = j;
		env->process[j].r[1] = id--;
		env->process[j].pc = i;
		env->process[j].cycles = check_cycles(env, j);
		env->process[j].carry = 0;
		env->process[j].live = -1;
		env->process[j].nb_live = 0;
		if (close(env->fd) < 0)
			return (FAIL);
		if (env->option == 1 || env->option == 2)
			write_champ_visu(env, j);
		i += 4096 / env->nb_process;
		j++;
	}
	return (SUCCESS);
}
