/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:01:25 by sabri             #+#    #+#             */
/*   Updated: 2019/05/31 16:58:22 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_sign(t_env *env, int index, int n)
{
	int nb;

	nb = 0;
	if (n == 2)
	{
		nb = env->memory[index] << 8;
		nb += env->memory[index + 1];
		if (env->memory[index] >> 7 == 1)
			nb = (char)nb;
	}
	else if (n == 4)
	{
		nb = env->memory[index] << 24;
		nb += env->memory[index + 1] << 16;
		nb += env->memory[index + 2] << 8;
		nb += env->memory[index + 3];
		if (nb  >> 15 == 1)
			nb = (char)nb;
	}
	return (nb);
}