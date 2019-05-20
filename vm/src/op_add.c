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
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = sum;
}
