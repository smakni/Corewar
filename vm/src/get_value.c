/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:45:20 by cmoulini          #+#    #+#             */
/*   Updated: 2019/07/01 12:09:59 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr(t_env *env, int value, unsigned int j)
{
	int		ret;

	ret = read_bytes(env->memory, env->process[j].pc + value, REG_SIZE);
	//ft_printf("ret = %i\n");
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
		*cursor += DIR_SIZE - 1;
	}
	else if (type_param(env->process[j].op.saved[1], param) == IND_CODE)
	{
		//ft_printf("ICI");
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, IND_SIZE) % IDX_MOD;
		value = get_addr(env, value, j);
		*cursor += IND_SIZE - 1;
	}
	if (env->verb == 1 && env->process[j].op.code != 0x03)
		save_ind_param(env, j, value, param - 1);
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
	else if (type_param(env->process[j].op.saved[1], param) == DIR_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, IND_SIZE);
		(*cursor) += IND_SIZE - 1;
	}
	else
	{
		(*cursor)++;
		value = read_bytes(env->process[j].op.saved, *cursor, IND_SIZE);
		value = get_addr(env, value, j);
		(*cursor) += IND_SIZE - 1;
	}
	if (env->verb == 1)
		save_ind_param(env, j, value, param - 1);
	return (value);
}
