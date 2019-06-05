#include	"../../includes/vm.h"

void	op_aff(t_env *env, unsigned j)
{
	int	reg;
	int	cursor;

	env->champ[j].op.name = "aff";
	env->champ[j].op.nb_params = 2;
	cursor = 1;
	reg = get_value(env, j, &cursor, 1);
	ft_putchar(reg % 256);
	env->champ[j].pc += cursor + 1;
}
