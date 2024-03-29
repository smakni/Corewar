/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:54:09 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 18:59:25 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_eol(t_parser *data, int i)
{
	if (data->line[i] == '"')
	{
		i++;
		while (data->line[i])
		{
			if (data->line[i] && data->line[i] != '\t' && data->line[i] != ' ')
				return (FAIL);
			i++;
		}
	}
	return (SUCCESS);
}
