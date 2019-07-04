/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:32:04 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/04 11:11:45 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int		check_pc(t_env *env, int j)
{
	if (env->process[j].pc >= MEM_SIZE)
		env->process[j].pc -= MEM_SIZE;
	else if (env->process[j].pc < 0)
		env->process[j].pc += MEM_SIZE;
	if (env->err_code != 0)
		return (FAIL);
	if ((env->process[j].cycles = check_cycles(env, j)) == 0)
	{
		env->process[j].pc++;
		if (env->option == 1 || env->option == 2)
			redraw_pc(env, env->process[j].pc, 1);
	}
	return (1);
}

int				processess_execution(t_env *env)
{
	int j;

	j = env->nb_process - 1;
	while (j >= 0)
	{
		if (env->process[j].nb_live >= 0)
		{
			if (env->process[j].cycles == 0)
			{
				if (check_pc(env, j) == FAIL)
					return (FAIL);
			}
			else if (env->process[j].cycles > 1)
				env->process[j].cycles--;
			if (env->process[j].cycles == 1)
				exec_op(env, j);
		}
		j--;
	}
	return (1);
}
