#include "../../includes/vm.h"

void		op_st(t_env *env ,unsigned j)
{
	int cursor;
	int	reg_content;
	int	dest;
	int	i;

	i = 0;
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
