#include "../../includes/vm.h"

void	op_sti(t_env *env, unsigned j)
{
	unsigned	reg_content;
	int			cursor;
	int			v1;
	int			dest;
	int			k;
	int			x;
	int			y;

	k = 0;
	dest = env->champ[j].pc;
	cursor = 1;
	reg_content = (unsigned)get_value_index(env, j, &cursor, 1);
	v1 = get_value_index(env, j, &cursor, 2);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == IND_CODE)
		dest += read_bytes(env, env->champ[j].pc + (v1 % IDX_MOD));
	else
		dest += get_value_index(env, j, &cursor, 2);
	dest += get_value_index(env, j, &cursor, 3);
	dest %= IDX_MOD;
	// ft_printf("%i\n", dest);
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
	env->champ[j].pc += 1 + cursor;
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
