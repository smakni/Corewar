#include "../../includes/vm.h"

void		op_sub(t_env *env ,int j)
{
	int cursor;
	int	reg_content;
	int	diff;

	cursor = 2;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	diff = reg_content;
	cursor++;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	diff -= reg_content;
	cursor++;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
	env->champ[j].pc += 1 + cursor;
}
