/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:54:09 by smakni            #+#    #+#             */
/*   Updated: 2019/07/25 19:04:10 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

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
