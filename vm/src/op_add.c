/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:57:09 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/29 00:10:25 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	set_reg(t_env *env, unsigned int j, int sum, int nb_reg)
{
	if (sum == 0)
		env->process[j].carry = 1;
	else
		env->process[j].carry = 0;
	env->process[j].op.name = "add";
	env->process[j].r[nb_reg] = sum;
}

static void	add_op(t_env *env, unsigned int j, int nb_reg, int *sum, int param)
{
	int reg_content;

	reg_content = env->process[j].r[nb_reg];
	if (env->verb == 1)
		save_param(env, j, nb_reg, REG_CODE, param);
	if (nb_reg >= 1 && nb_reg <= REG_NUMBER)
		*sum += reg_content;
}

void		op_add(t_env *env, unsigned int j)
{
	int cursor;
	int nb_reg[3];
	int	sum;

	cursor = 1;
	if (check_args(env, j, &cursor, 3))
	{
		sum = 0;
		nb_reg[0] = env->process[j].op.saved[2];
		add_op(env, j, nb_reg[0], &sum, 0);
		nb_reg[1] = env->process[j].op.saved[3];
		add_op(env, j, nb_reg[1], &sum, 1);
		nb_reg[2] = env->process[j].op.saved[4];	
		if (env->verb == 1)
			save_param(env, j, nb_reg[2], REG_CODE, 2);
		if (nb_reg[0] >= 1 && nb_reg[0] <= REG_NUMBER
				&& nb_reg[1] >= 1 && nb_reg[1] <= REG_NUMBER
				&& nb_reg[2] >= 1 && nb_reg[2] <= REG_NUMBER)
			set_reg(env, j, sum, nb_reg[2]);
		cursor += 4;
	}
	else
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 3);
	env->process[j].pc += cursor;
}
