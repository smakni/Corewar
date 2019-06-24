/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:12:56 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/24 17:02:47 by smakni           ###   ########.fr       */
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

	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		cursor++;
		nb_reg1 = env->process[j].op.saved[cursor];
		save_param(env, j, nb_reg1, REG_CODE, 0);
		if (nb_reg1 >= 1 && nb_reg1 <= 16)
		{
			reg_content = env->process[j].r[env->process[j].op.saved[cursor]];
			diff = reg_content;
		}
		else
			diff = 0;
		cursor++;
		nb_reg2 = env->process[j].op.saved[cursor];
		save_param(env, j, nb_reg2, REG_CODE, 1);
		//if (env->visu == 0)
		//	ft_printf("nb_reg2 = %i\n", nb_reg2);
		if (nb_reg2 >= 1 && nb_reg2 <= 16)
		{
			reg_content = env->process[j].r[env->process[j].op.saved[cursor]];
			diff -= reg_content;
		}
		cursor++;
		nb_reg3 = env->process[j].op.saved[cursor];
			save_param(env, j, nb_reg3, REG_CODE, 2);

		if (diff == 0 && nb_reg1 >= 1 && nb_reg1 <= 16
				&& nb_reg2 >= 1 && nb_reg2 <= 16
				&& nb_reg3 >= 1 && nb_reg3 <= 16)
			env->process[j].carry = 1;
		else
			env->process[j].carry = 0;
		if (nb_reg1 >= 1 && nb_reg1 <= 16 && nb_reg2 >= 1 && nb_reg2 <= 16 && nb_reg3 >= 1 && nb_reg3 <= 16)
		{
			env->process[j].op.name = "sub";
			env->process[j].r[env->process[j].op.saved[cursor]] = diff;
		}
		cursor++;
	}
else if (cursor == 1)
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	env->process[j].pc += cursor;
}
