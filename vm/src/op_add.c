/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:57:09 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/13 17:58:25 by smakni           ###   ########.fr       */
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
		env->proc[j].op.name = "add";
		cursor++;
		sum = 0;
		nb_reg1 = env->proc[j].op.saved[cursor];
		save_param(env, j, nb_reg1, REG_CODE, 0);
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
		{
			reg_content = env->proc[j].r[nb_reg1];
			sum += reg_content;
		}
		cursor++;
		nb_reg2 = env->proc[j].op.saved[cursor];
		save_param(env, j, nb_reg2, REG_CODE, 1);
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
		{
			reg_content = env->proc[j].r[nb_reg2];
			sum += reg_content;
		}
		cursor++;
		nb_reg3 = env->proc[j].op.saved[cursor];
		save_param(env, j, nb_reg3, REG_CODE, 2);
		if (sum == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
				&& nb_reg2 >= 1 && nb_reg2 <= 16
				&& nb_reg3 >= 1 && nb_reg3 <= 16)
			env->proc[j].carry = 1;
		else
			env->proc[j].carry = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
			env->proc[j].r[nb_reg3] = sum;
		cursor++;
	}
	else
		cursor += decode_byte_param(env->proc[j].op.saved[1], 0, 3);
	env->proc[j].pc += cursor;
}
