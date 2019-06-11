/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:24:52 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 21:43:11 by jergauth         ###   ########.fr       */
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
		env->champ[j].op.name = "aff";
		reg = get_value(env, j, &cursor, 1);
		ft_putchar(reg % 256);
		cursor++;
	}
	else
		cursor += decode_byte_param(env->memory[env->champ[j].pc + 1], 0, 1);
	env->champ[j].pc += cursor;
}
