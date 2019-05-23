#include	"../../includes/vm.h"

void	op_aff(t_env *env, int j)
{
	int	reg;
	int	cursor;

	cursor = 1;
	reg = get_value(env, j, &cursor, 1);
	ft_putchar(reg % 256);
	env->champ[j].pc += cursor + 1;
}
