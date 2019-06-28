/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:45:20 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/29 01:03:00 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr(t_env *env, int value, unsigned int j)
{
	int	ret;

	ret = read_bytes(env->memory, (env->process[j].pc + value) % IDX_MOD, REG_SIZE);
	return (ret);
}

int			get_value(t_env *env, unsigned j, int *cursor, int param)
{
	int	value;

	value = 0;
	if (type_param(env->process[j].op.saved[1], param) == REG_CODE)
	{
		(*cursor)++;
		value = env->process[j].r[env->process[j].op.saved[*cursor]];
	}
	else if (type_param(env->process[j].op.saved[1], param) == DIR_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, DIR_SIZE);
		//save_param(env, j, value, DIR_CODE);
		*cursor += DIR_SIZE - 1;
	}
	else if (type_param(env->process[j].op.saved[1], param) == IND_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, IND_SIZE);
		//save_param(env, j, value, IND_CODE);
		value = get_addr(env, value, j);
		*cursor += IND_SIZE - 1;
	}
	if (env->verb == 1)
		save_param(env, j, value, IND_CODE, param - 1);
	return (value);
}

int			get_value_index(t_env *env, unsigned j, int *cursor, int param)
{
	int	value;

	value = 0;
	if (type_param(env->process[j].op.saved[1], param) == REG_CODE)
	{
		(*cursor)++;
		value = env->process[j].r[env->process[j].op.saved[*cursor]];
	}
	else
	{
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, IND_SIZE);
		//if (type_param(env->process[j].op.saved[1], param) == IND_CODE)
			//save_param(env, j, value, IND_CODE);
		//else
			//save_param(env, j, value, DIR_CODE);
		(*cursor) += IND_SIZE - 1;
	}
	if (env->verb == 1)
		save_param(env, j, value, IND_CODE, param - 1);
	return (value);
}
