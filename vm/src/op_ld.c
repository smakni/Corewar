/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:40:14 by smakni            #+#    #+#             */
/*   Updated: 2019/05/20 17:54:14 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int    type_param(unsigned char byte, int param)
{
    char    mask;
    char    tmp;

    mask = 0b00000011;
    tmp = mask & (byte >> ((3 - param + 1) * 2));
    return (tmp);
}

void		op_ld(t_env *env ,int j)
{
	int r_index;
	int	to_store;
	int	mem_index;

	if (type_param(env->memory[env->champ[j].pc], 1) == 4)
	{
		mem_index = env->champ[j].pc + env->memory[env->champ[j].pc + 5] + 3;
		r_index = env->memory[env->champ[j].pc + 6];
	}
	else
	{
		mem_index = env->champ[j].pc + env->memory[env->champ[j].pc + 3] + 3;
		r_index = env->memory[env->champ[j].pc + 4];
	}
	to_store = read_multi_bytes(env->memory, mem_index, DIR_SIZE);
	ft_printf("mem_index = %x\n", mem_index);
	ft_printf("to_store = %x\n", to_store);
	env->champ[j].r[r_index] = to_store;
	ft_printf("r_index = %x\n", r_index);
	env->champ[j].carry = 1;
}