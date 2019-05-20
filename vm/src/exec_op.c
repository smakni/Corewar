/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:24:48 by smakni            #+#    #+#             */
/*   Updated: 2019/05/20 13:28:37 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		exec_op(t_env *env, int j)
{
	if (env->memory[env->champ[j].pc] == 0x01)
	{	
		ft_printf("live\n");
		return (5);
	}
	else if (env->memory[env->champ[j].pc] == 0x02)
	{
		ft_printf("ld\n");
		return (3 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x03)
	{
		ft_printf("st\n");
		return (3 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x04)
	{
		ft_printf("add\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x05)
	{
		ft_printf("sub\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x06)
	{
		ft_printf("and\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x07)
	{
		ft_printf("or\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x08)
	{
		ft_printf("xor\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x09)
	{
		ft_printf("zjump\n");
		return (2);
	}
	else if (env->memory[env->champ[j].pc] == 0x0a)
	{
		ft_printf("ldi\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x0b)
	{
		ft_printf("sti\n");
		return (4 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x0c)
	{
		ft_printf("fork\n");
		return (2);
	}
	else if (env->memory[env->champ[j].pc] == 0x0d)
	{
		ft_printf("lld\n");
		return (3 + 1);
	}
	else if (env->memory[env->champ[j].pc] == 0x0e)
	{
		ft_printf("lldi\n");
		return (4);
	}
	else if (env->memory[env->champ[j].pc] == 0x0f)
	{
		ft_printf("lfork\n");
		return (2);
	}
	else if (env->memory[env->champ[j].pc] == 0x10)
	{
		ft_printf("aff\n");
		return (2 + 1);
	}
	return (0);
}