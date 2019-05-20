#include "../../includes/vm.h"

static int	type_param(unsigned char byte, int param)
{
	char	mask;
	char	tmp;

	mask = 0b00000011;
	tmp = mask & (byte >> ((3 - param + 1) * 2));
	return (tmp);
}

void	op_sti(t_env *env, int j)
{
	int		reg_content;
	int		cursor;
	short	dest;

	dest = 0;
	cursor = 2;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == REG_CODE)
	{
		cursor++;
		dest += env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	}
	else
	{
		cursor += 2;
		dest += read_multi_bytes(env->memory, env->champ[j].pc + cursor, 2);
	}
	if (type_param(env->memory[env->champ[j].pc + 1], 3) == REG_CODE)
	{
		cursor++;
		dest += env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	}
	else
	{
		cursor += 2;
		dest += read_multi_bytes(env->memory, env->champ[j].pc + cursor, 2);
	}
	dest += env->champ[j].pc;
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
}
