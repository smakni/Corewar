#include "../../includes/vm.h"

void		op_and(t_env *env, unsigned j)
{
	int cursor;
	int	value;
	int	diff;

	cursor = 1;
	diff = get_value(env, j, &cursor, 1);
	value = get_value(env, j, &cursor, 2);
	diff &= value;
	cursor++;
	if (diff == 0)
		env->champ[j].carry = 1;
	else
		env->champ[j].carry = 0;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
	env->champ[j].pc += 1 + cursor;
}
