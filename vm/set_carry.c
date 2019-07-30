/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_carry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:21:14 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/30 11:21:53 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_carry(t_env *env, unsigned int j, int value)
{
	if (value == 0)
		env->process[j].carry = 1;
	else
		env->process[j].carry = 0;
}
