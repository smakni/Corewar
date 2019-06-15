/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:24:52 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/13 17:41:02 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

void	op_aff(t_env *env, unsigned j)
{
	int	reg;
	int	cursor;

	cursor = 1;
	if (check_args(env, j, &cursor, 1))
	{
		env->process[j].op.name = "aff";
		reg = get_value(env, j, &cursor, 1);
		ft_putchar(reg % 256);
		cursor++;
	}
	else
		cursor += decode_byte_param(env->process[j].op.saved[1], 0, 1);
	env->process[j].pc += cursor;
}
