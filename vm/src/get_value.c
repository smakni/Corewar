/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:45:20 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/05 00:05:40 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr(t_env *env, int value, unsigned int j)
{
	int	ret;

	ret = read_bytes(env->memory, (env->champ[j].pc + value) % IDX_MOD, 4);
	return (ret);
}

int			get_value(t_env *env, unsigned j, int *cursor, int param)
{
	int	value;

	value = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], param) == REG_CODE)
	{
		(*cursor)++;
		value = env->champ[j].r[env->memory[env->champ[j].pc + *cursor]];
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == DIR_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, DIR_SIZE);
		*cursor += DIR_SIZE - 1;
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == IND_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
		value = get_addr(env, value, j);
		if (env->visu == 0)
			ft_printf("value ind = %i\n", value);
		*cursor += IND_SIZE - 1;
	}
	return (value);
}

int			get_value_index(t_env *env, unsigned j, int *cursor, int param)
{
	int	value;

	value = 0;
	if (type_param(env->memory[env->champ[j].pc + 1], param) == REG_CODE)
	{
		(*cursor)++;
		value = env->champ[j].r[env->memory[env->champ[j].pc + *cursor]];
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == DIR_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, DIR_SIZE);
		(*cursor) += DIR_SIZE - 1;
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == IND_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
		(*cursor) += IND_SIZE - 1;
	}
	return (value);
}
