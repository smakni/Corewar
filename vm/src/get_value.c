#include "../../includes/vm.h"

static int	get_addr(t_env *env, int value)
{
	int	ret;

	ret = read_bytes(env->memory, (value - 1) % IDX_MOD, DIR_SIZE);
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
		//ft_printf("mem %#x\n", env->memory[env->champ[j].pc + *cursor]);
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
		value = get_addr(env, value);
		*cursor += IND_SIZE - 1;
	}
	//ft_printf("value %i\n", value);
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
	//ft_printf("value %i\n", value);
	return (value);
}
