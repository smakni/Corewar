
#include "../../includes/vm.h"

static void	intro_game(t_env *env)
{
	unsigned i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < env->nb_champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
					env->live[i].header.prog_size, env->live[i].header.prog_name, 
					env->live[i].header.comment);
		i++;
	}
}

static int check_live(t_env *env, int *check_delta)
{
	int living_proc;

	living_proc = del_process(env);
	if (env->live_period >= NBR_LIVE)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env ->visu == 0)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
	}
	else
		(*check_delta)++;
	env->live_period = 0;
	return (living_proc);
}

static int	move_pc(t_env *env, int j)
{
	if (env->champ[j].pc >= MEM_SIZE)
		env->champ[j].pc -= MEM_SIZE;
	else if (env->champ[j].pc < 0)
		env->champ[j].pc += MEM_SIZE;
	if (env->err_code != 0)
		return (FAIL);
	ft_bzero(&(env->champ[j].op), sizeof(t_op));
	env->champ[j].cycles = check_cycles(env, j);
	return (1);
}

static int	process_execution(t_env *env)
{
	int j;

	j = env->nb_champs - 1;
	while (j >= 0)
	{
		if (env->champ[j].nb_live >= 0)
		{
			if (env->champ[j].cycles == 1)
			{
				exec_op(env, j);
				if (move_pc(env, j) == FAIL)
					return (FAIL);
			}
			else if (env->champ[j].cycles > 1)
				env->champ[j].cycles--;
		}
		j--;
	}
	return (1);
}

static int reset_cycles(t_env *env, int *check_delta)
{
	if (*check_delta == MAX_CHECKS)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env->visu == 0)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		*check_delta = 0;
	}
	return (0);
}

int read_memory(t_env *env)
{
	int i;
	int check_delta;

	i = 0;
	check_delta = 0;
	env->cycle_index = 1;
	env->cycle_to_die = CYCLE_TO_DIE;
	if (env->visu == 0)
		intro_game(env);
	while (env->cycle_to_die > 0)
	{
		if (env->cycle_index == 3229)
			ft_printf("DEBUG\n");
		if (env->cycle_index == 3900)
			ft_printf("DEBUG\n");
		if (env->cycle_index == 4570)
			ft_printf("DEBUG\n");
		if (i == env->cycle_to_die)
		{
			if (check_live(env, &check_delta) == 0)
				break ;
			i = reset_cycles(env, &check_delta);
		}
		if (env->visu == 0)
			ft_printf("It is now cycle %d\n", env->cycle_index);
		if (process_execution(env) == FAIL)
			return (FAIL);
		if (env->visu == 1)
		{
			print_infos(env);
			wrefresh(env->mem);
			key_events(env);
		}
		// else
		// 	ft_print_memory(env);
		// read(0, 0, 1);
		env->cycle_index++;
		i++;
		//remove_bold(env);
	}
	return (SUCCESS);
}
