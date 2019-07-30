/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:57:09 by cmoulini          #+#    #+#             */
/*   Updated: 2019/07/30 11:22:18 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	set_reg(t_env *env, unsigned int j, int sum, int nb_reg)
{
	set_carry(env, j, sum);
	env->process[j].op.name = "add";
	env->process[j].r[nb_reg] = sum;
}

static int	add_op(t_env *env, unsigned int j, int nb_reg, int param)
{
	int reg_content;
	int	ret;

	reg_content = env->process[j].r[nb_reg];
	ret = 0;
	if (env->verb == 1)
		save_reg_param(env, j, nb_reg, param);
	if (nb_reg >= 1 && nb_reg <= REG_NUMBER)
		ret += reg_content;
	return (ret);
}

void		op_add(t_env *env, unsigned int j)
{
	int cursor;
	int nb_reg[3];
	int	sum;

	cursor = 1;
	if (check_args(env, j, cursor, 3))
	{
		nb_reg[0] = env->process[j].op.saved[2];
		sum = add_op(env, j, nb_reg[0], 0);
		nb_reg[1] = env->process[j].op.saved[3];
		sum += add_op(env, j, nb_reg[1], 1);
		nb_reg[2] = env->process[j].op.saved[4];
		if (env->verb == 1)
			save_reg_param(env, j, nb_reg[2], 2);
		if (all_reg_valid(nb_reg, 3))
			set_reg(env, j, sum, nb_reg[2]);
		cursor += 4;
	}
	else
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	env->process[j].pc += cursor;
}
