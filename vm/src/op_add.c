/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:57:09 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 20:17:32 by cmoulini         ###   ########.fr       */
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

	env->champ[j].op.name = "add";
	env->champ[j].op.nb_params = 3;
	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		cursor++;
		sum = 0;
		nb_reg1 = env->memory[env->champ[j].pc + cursor];
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			sum += reg_content;
		}
		cursor++;
		nb_reg2 = env->memory[env->champ[j].pc + cursor];
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
		{
			reg_content = env->champ[j].r[env->memory[env->champ[j].pc + cursor]];
			sum += reg_content;
		}
		cursor++;
		nb_reg3 = env->memory[env->champ[j].pc + cursor];
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
