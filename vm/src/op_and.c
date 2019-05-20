#include "../../includes/vm.h"

void		op_and(t_env *env, int j)
{
	int cursor;
	int	value;
	int	diff;

	cursor = 1;
	diff = get_value(env, j, &cursor, 1);
	value = get_value(env, j, &cursor, 2);
	diff &= value;
	cursor++;
	env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
}
