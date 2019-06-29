/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:56:33 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/06/29 19:56:34 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		ft_print_memory(t_env *env)
{
	int	i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < 4096)
	{
		ft_printf("%.2x ", env->memory[i]);
		i++;
		if (i % DUMP == 0)
		{
			if (i != 4096)
				ft_printf("\n%#.4x : ", i);
			else
				ft_putendl("");
		}
	}
}
