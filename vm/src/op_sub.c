#include "../../includes/vm.h"

void		op_sub(t_env *env ,unsigned j)
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
	if (diff == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
	env->champ[j].pc += 1 + cursor;
}
