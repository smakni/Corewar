/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:13:42 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/01 11:45:52 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		print_live(t_env *env, unsigned j)
{
	char	*tmp;
	int		save;

	save = ft_atoi(&env->process[j].op.param[0][1]) - 1;
	tmp = env->player[save].header.prog_name;
	ft_printf("\nPlayer %c (%s) is said to be alive",
						env->process[j].op.param[0][1], tmp);
}

void		print_ldi_lldi(t_env *env, unsigned j, int save)
{
	int	tmp;

	tmp = ft_atoi(env->process[j].op.param[0])
						+ ft_atoi(env->process[j].op.param[1]);
	if (env->process[j].op.code == 0x0a)
		ft_printf("\n       | -> load from %s + %s = %d (with pc and mod %d)",
					env->process[j].op.param[0], env->process[j].op.param[1],
					tmp, save + (tmp % IDX_MOD));
	else
		ft_printf("\n       | -> load from %s + %s = %d (with pc %d)",
					env->process[j].op.param[0], env->process[j].op.param[1],
					tmp, save + (tmp % IDX_MOD));
}

void		print_sti(t_env *env, unsigned j, int save)
{
	int	tmp;

	tmp = ft_atoi(env->process[j].op.param[1])
						+ ft_atoi(env->process[j].op.param[2]);
	ft_printf("\n       | -> store to %s + %s = %d (with pc and mod %d)",
				env->process[j].op.param[1], env->process[j].op.param[2],
				tmp, save + (tmp % IDX_MOD));
}

void		print_verbos(t_env *env, unsigned j, int save)
{
	int	i;

	i = 0;
	ft_printf("%s", env->process[j].op.name);
	while (env->process[j].op.param[i])
		ft_printf(" %s", env->process[j].op.param[i++]);
	if (env->process[j].op.code == 0x01
			&& (ft_strcmp(env->process[j].op.param[0], "-1") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-2") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-3") == 0
				|| ft_strcmp(env->process[j].op.param[0], "-4") == 0))
		print_live(env, j);
	else if (env->process[j].op.code == 0x0b && env->process[j].check_args == 1)
		print_sti(env, j, save);
	else if ((env->process[j].op.code == 0x0a || env->process[j].op.code == 0x0e) && env->process[j].check_args == 1)
		print_ldi_lldi(env, j, save);
	ft_putendl("");
}

void		verbos(t_env *env, unsigned j, int save)
{
	int	i;

	i = 0;
	if (env->process[j].op.name != NULL)
		ft_printf("P %4d | ", j + 1);
	if (env->process[j].op.code == 0x09 && env->process[j].carry == 1)
	{
		ft_printf("zjmp %d OK\n", read_bytes(env->process[j].op.saved, 1, 2));
		return ;
	}
	else if (env->process[j].op.code == 0x09 && env->process[j].carry == 0)
		ft_printf("zjmp %d FAILED\n",
							read_bytes(env->process[j].op.saved, 1, 2));
	else if (env->process[j].op.code == 0x0c)
		ft_printf("fork %d (%d)\n", read_bytes(env->process[j].op.saved, 1, 2),
							save + read_bytes(env->process[j].op.saved, 1, 2));
	else if (env->process[j].op.code == 0x0f)
		ft_printf("lfork %d (%d)\n", read_bytes(env->process[j].op.saved, 1, 2),
							save + read_bytes(env->process[j].op.saved, 1, 2));
	else if (env->process[j].op.name != NULL)
		print_verbos(env, j, save);
	print_pc(env, j, save);
	while (env->process[j].op.param[i])
		free(env->process[j].op.param[i++]);
}
