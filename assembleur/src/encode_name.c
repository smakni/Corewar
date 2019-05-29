/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:48:42 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/29 16:51:26 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		encode_name(t_parser *data, int i)
{
	data->index++;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	if (data->index > 0x8b)
		return (FAIL);
	return (SUCCESS);
}

int		encode_multi_name(t_parser *data)
{
	data->bytecode[data->index] = 0x0a;
	ft_strdel(&data->line);
	while (get_next_line(data->fd, &data->line, &data->eol) > 0
			&& ft_strchr(data->line, '\"') == NULL)
	{
		if (!(encode_name(data, 0)))
			return (FAIL);
		ft_strdel(&data->line);
		data->bytecode[data->index] = 0x0a;
		data->nb_line++;
	}
	if (!(encode_name(data, 0)))
		return (FAIL);
	data->nb_line++;
	return (SUCCESS);
}