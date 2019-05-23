#include "../../includes/vm.h"

void		op_st(t_env *env ,int j)
{
	int cursor;
	int	reg_content;
	int	dest;

	cursor = 2;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	ft_printf("reg num -> %x\nreg_cont = %x\n", env->memory[env->champ[j].pc + cursor], reg_content);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == IND_CODE)
		cursor += IND_SIZE;
	else
		cursor += REG_SIZE;
	dest = read_multi_bytes(env->memory, env->champ[j].pc + cursor, IND_SIZE);
	dest = (env->champ[j].pc + dest) % IDX_MOD;
	ft_printf("reg content %x\n", reg_content);
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
	env->champ[j].pc += 1 + cursor;
}
