#include "../../includes/vm.h"

void	op_sti(t_env *env, int j)
{
	unsigned	reg_content;
	int			cursor;
	short		dest;

	dest = env->champ[j].pc;
	cursor = 1;
	reg_content = (unsigned)get_value_index(env, j, &cursor, 1);
	dest += get_value_index(env, j, &cursor, 2);
	dest += get_value_index(env, j, &cursor, 3);
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
	env->champ[j].pc += 1 + cursor;
}
