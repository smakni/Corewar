/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:07:10 by cmoulini          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	fail_routine(t_env *env, unsigned int j)
{
	env->process[j].check_args = 0;
	return (0);
}

int			check_args(t_env *env, unsigned int j, int cursor, int nb_param)
{
	int	tmp;
	int	mask;
	int	encode_byte;

	if (env->process[j].op.code != env->process[j].op.saved[0])
		return (0);
	mask = 0b00000011;
	encode_byte = env->process[j].op.saved[cursor];
	tmp = nb_param * 2;
	if ((0b11111111 & (encode_byte << tmp)) != 0)
		return (fail_routine(env, j));
	while (nb_param > 0)
	{
		tmp = encode_byte >> (8 - nb_param * 2);
		tmp &= mask;
		if ((tmp | 0b00000000) == 0)
			return (fail_routine(env, j));
		nb_param--;
	}
	env->process[j].check_args = 1;
	return (1);
}
