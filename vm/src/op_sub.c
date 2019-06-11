/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:12:56 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 14:26:52 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_sub(t_env *env, unsigned int j)
{
	int cursor;
	int	reg_content;
	int	nb_reg1;
	int	nb_reg2;
	int	nb_reg3;
	int	diff;

	env->champ[j].op.name = "sub";
	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		cursor++;
		nb_reg1 = env->memory[env->champ[j].pc + cursor];
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			diff = reg_content;
		}
		else
			diff = 0;
		cursor++;
		nb_reg2 = env->memory[env->champ[j].pc + cursor];
		if (env->visu == 0)
			ft_printf("nb_reg2 = %i\n", nb_reg2);
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			diff -= reg_content;
		}
		cursor++;
		nb_reg3 = env->memory[env->champ[j].pc + cursor];
		if (diff == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
				&& nb_reg2 >= 1 && nb_reg2 <= 16
				&& nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].carry = 1;
		else
			env->champ[j].carry = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = diff;
		cursor++;
	}
	env->champ[j].pc += cursor;
}
