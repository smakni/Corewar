#include "../../includes/vm.h"

void	op_sti(t_env *env, unsigned j)
{
	unsigned	reg_content;
	int			cursor;
	short		dest;
	int			i;

	i = 0;
	dest = env->champ[j].pc;
	cursor = 1;
	reg_content = (unsigned)get_value_index(env, j, &cursor, 1);
	dest += get_value_index(env, j, &cursor, 2);
	dest += get_value_index(env, j, &cursor, 3);
	env->memory[dest] = reg_content >> 24;
	env->memory[dest + 1] = reg_content >> 16;
	env->memory[dest + 2] = reg_content >> 8;
	env->memory[dest + 3] = reg_content;
	if (env->visu == 1)
	{
		if (env->champ[j].player_nb == 0xffffffff)
			wattron(env->mem, COLOR_PAIR(4));
		else if (env->champ[j].player_nb == 0xfffffffe)
			wattron(env->mem, COLOR_PAIR(5));
		else if (env->champ[j].player_nb == 0xfffffffd)
			wattron(env->mem, COLOR_PAIR(6));
		else if (env->champ[j].player_nb == 0xfffffffc)
			wattron(env->mem, COLOR_PAIR(7));
		while (i < 4)
		{
			mvwprintw(env->mem, (dest + i) / 64, (dest + i) % 64 * 3, "%.2x", env->memory[dest + i]);
			i++;
		}
		wrefresh(env->mem);
	}
	env->champ[j].pc += 1 + cursor;
}
