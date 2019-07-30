/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_reg_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:07:58 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/30 11:10:29 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		all_reg_valid(const int	*tab, const unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (tab[i] < 1 || tab[i] > REG_NUMBER)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
