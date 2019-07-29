/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:06:32 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_parse_args(t_parser *data, char **params)
{
	int		i;
	char	byte;
	int		tmp;

	i = 0;
	byte = 0;
	while (params[i])
	{
		if (!(tmp = ft_encode_byte_param(params[i])))
			return (FAIL);
		byte += tmp;
		byte <<= 2;
		i++;
	}
	while (i < 3)
	{
		byte <<= 2;
		i++;
	}
	data->bytecode[data->index] = byte;
	data->index++;
	return (SUCCESS);
}
