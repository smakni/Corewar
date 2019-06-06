/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:45:20 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 18:55:26 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	get_addr(t_env *env, int value, unsigned int j)
{
	int	ret;

	ret = read_bytes(env->memory, (env->champ[j].pc + value) % IDX_MOD, REG_SIZE);
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
		save_param(env, j, value, REG_CODE);
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == DIR_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, DIR_SIZE);
		save_param(env, j, value, DIR_CODE);
		*cursor += DIR_SIZE - 1;
	}
	else if (type_param(env->memory[env->champ[j].pc + 1], param) == IND_CODE)
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
		save_param(env, j, value, IND_CODE);
		value = get_addr(env, value, j);
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
		save_param(env, j, value, REG_CODE);
	}
	else
	{
		(*cursor)++;
		value = read_bytes(env->memory, env->champ[j].pc + *cursor, IND_SIZE);
		if (type_param(env->memory[env->champ[j].pc + 1], param) == IND_CODE)
			save_param(env, j, value, IND_CODE);
		else
			save_param(env, j, value, DIR_CODE);
		(*cursor) += IND_SIZE - 1;
	}
	return (value);
}
