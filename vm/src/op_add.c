#include "../../includes/vm.h"

void		op_add(t_env *env ,int j)
{
	int cursor;
	int	reg_content;
	int	sum;

	cursor = 2;
	sum = 0;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	sum += reg_content;
	cursor++;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	sum += reg_content;
	cursor++;
	if (sum == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = sum;
	env->champ[j].pc += 1 + cursor;
}
