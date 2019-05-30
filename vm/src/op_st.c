#include "../../includes/vm.h"

void op_st(t_env *env, unsigned j)
{
	int cursor;
	int reg_content;
	int dest;
	int k;
	int			x;
	int			y;

	k = 0;
	cursor = 2;
	reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
	//ft_printf("reg num -> %x\nreg_cont = %x\n", env->memory[env->champ[j].pc + cursor], reg_content);
	if (type_param(env->memory[env->champ[j].pc + 1], 2) == IND_CODE)
		cursor += IND_SIZE;
	else
		cursor += REG_SIZE;
	dest = read_multi_bytes(env->memory, env->champ[j].pc + cursor, IND_SIZE);
	dest = (env->champ[j].pc + dest) % IDX_MOD;
	//ft_printf("reg content %x\n", reg_content);
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
