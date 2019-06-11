/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:04:01 by smakni            #+#    #+#             */
/*   Updated: 2019/06/06 18:00:38 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int			op_len(t_env *env, unsigned j)
{
	int 	op_len_tab[16];

	if (env->memory[env->champ[j].pc] == 01)
		return (5);
	else if (env->memory[env->champ[j].pc] == 02)
		return (1 + decode_byte_param(env->memory[env->champ[j].pc + 1], 0));
}

void		save_op(t_env *env, unsigned j)
{
	ft_memcpy(env->champ[j].op.saved, env->memory[env->champ[j].pc], op_len(env, j));
}
