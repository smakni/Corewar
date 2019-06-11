/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:57:09 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 17:46:57 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_add(t_env *env, unsigned int j)
{
	int cursor;
	int	reg_content;
	int	nb_reg1;
	int	nb_reg2;
	int	nb_reg3;
	int	sum;

	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		env->champ[j].op.name = "add";
		cursor++;
		sum = 0;
		nb_reg1 = env->memory[env->champ[j].pc + cursor];
		save_param(env, j, nb_reg1, REG_CODE, 0);
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			sum += reg_content;
		}
		cursor++;
		nb_reg2 = env->memory[env->champ[j].pc + cursor];
		save_param(env, j, nb_reg2, REG_CODE, 1);
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			sum += reg_content;
		}
		cursor++;
		nb_reg3 = env->memory[env->champ[j].pc + cursor];
		save_param(env, j, nb_reg3, REG_CODE, 2);
		if (sum == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
				&& nb_reg2 >= 1 && nb_reg2 <= 16
				&& nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].carry = 1;
		else
			env->champ[j].carry = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
			env->champ[j].r[env->memory[env->champ[j].pc + cursor]] = sum;
		cursor++;
	}
	env->champ[j].pc += cursor;
}
