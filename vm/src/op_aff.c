/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:24:52 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 20:25:02 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

void	op_aff(t_env *env, unsigned j)
{
	int	reg;
	int	cursor;

	env->champ[j].op.name = "aff";
	env->champ[j].op.nb_params = 1;
	cursor = 1;
	if (check_args(env, j, &cursor, 1))
	{
		reg = get_value(env, j, &cursor, 1);
		ft_putchar(reg % 256);
		cursor++;
	}
	env->champ[j].pc += cursor;
}
