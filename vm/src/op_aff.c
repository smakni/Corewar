/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:24:52 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 19:24:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

void	op_aff(t_env *env, unsigned j)
{
	int	reg;
	int	cursor;

	env->champ[j].op.name = "aff";
	cursor = 1;
	if (check_args(env, j, &cursor, 1))
	{
		reg = get_value(env, j, &cursor, 1);
		ft_putchar(reg % 256);
		cursor++;
	}
	else
		cursor = 3;
	env->champ[j].pc += cursor;
}
