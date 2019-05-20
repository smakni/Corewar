#include "../../includes/vm.h"

void		op_st(t_env *env ,int j)
{
	int cursor;
	int	reg_content;
	int	dest;

	cursor = 2;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == IND_CODE)
		cursor += IND_SIZE;
	else
		cursor += REG_SIZE;
	dest = read_multi_bytes(env->memory, env->champ[j].pc + cursor, IND_SIZE);
	dest = (env->champ[j].pc + dest) % IDX_MOD;
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
}
