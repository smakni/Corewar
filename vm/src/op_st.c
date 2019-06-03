#include "../../includes/vm.h"

static int	read_two_bytes(t_env *env, int current_pos, int *cursor)
{
	short	v1;
	short	v2;
	short	ret;

	v1 = env->memory[current_pos + *cursor];
	//ft_printf("v1 %i @ %i\n", v1, *cursor);
	(*cursor)++;
	v2 = env->memory[current_pos + *cursor];
	(*cursor)++;
//	ft_printf("v2 %i\n", v2);
	ret = v2 - v1;
	if (ret < 0)
		ret--;
	return (ret);
}

void op_st(t_env *env, unsigned j)
{
	int		cursor;
	short	dest;
	int		reg_content;
	int		current_pos;

	current_pos = env->champ[j].pc;
//ft_printf("cur pos %i\n", current_pos);
	cursor = 1;
	reg_content = get_value(env, j, &cursor, 1);
	cursor++;
	if (type_param(env->memory[current_pos + 1], 2) == IND_CODE)
	{
		dest = read_two_bytes(env, current_pos, &cursor) % IDX_MOD;
		if (current_pos + dest < 0)
			dest = current_pos + dest + MEM_SIZE;
		else if (current_pos + dest >= MEM_SIZE)
			dest = current_pos + dest % MEM_SIZE;
		env->memory[dest] = reg_content >> 24;
		env->memory[dest + 1] = reg_content >> 16;
		env->memory[dest + 2] = reg_content >> 8;
		env->memory[dest + 3] = reg_content;
	}
	else
	{
		dest = env->memory[env->champ[j].pc + cursor];
		cursor++;
//		ft_printf("dest reg %i\n", dest);
		env->champ[j].r[dest] = reg_content;
	}
	env->champ[j].pc += cursor;
	if (env->visu == 1)
		update_visu(env, dest, j);
}
