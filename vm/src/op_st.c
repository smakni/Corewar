#include "../../includes/vm.h"

static int	read_two_bytes(t_env *env, int current_pos, int *cursor)
{
	short	v1;
	short	v2;
	short	ret;

	v1 = env->memory[current_pos + *cursor];
	ft_printf("v1 %i @ %i\n", v1, *cursor);
	(*cursor)++;
	v2 = env->memory[current_pos + *cursor];
	(*cursor)++;
	ft_printf("v2 %i\n", v2);
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
	int k;
	int			x;
	int			y;

	k = 0;
	current_pos = env->champ[j].pc;
ft_printf("cur pos %i\n", current_pos);
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
		ft_printf("dest reg %i\n", dest);
		env->champ[j].r[dest] = reg_content;
	}
	env->champ[j].pc += cursor;

	mvwprintw(env->infos, 1, 6, "dest:%d", dest);
	if (env->visu == 1)
	{
		if (env->champ[j].player_nb == 0xffffffff)
			j = 0;
		else if (env->champ[j].player_nb == 0xfffffffe)
			j = 1;
		else if (env->champ[j].player_nb == 0xfffffffd)
			j = 2;
		else if (env->champ[j].player_nb == 0xfffffffc)
			j = 3;
		wattron(env->mem, COLOR_PAIR(4 + j));
		x = dest % 64 * 3;
		y = dest / 64;
		while (k < 4)
		{
			mvwprintw(env->mem, y, x, "%.2x", env->memory[dest + k]);
			x += 3;
			if (x >= 192)
			{
				x -= 192;
				y++;
			}
			k++;
		}
		wrefresh(env->mem);
	}
}
