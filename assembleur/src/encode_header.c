/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:41:43 by smakni            #+#    #+#             */
/*   Updated: 2019/05/15 18:16:51 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		encode_comment(t_parser *data, int i)
{
	data->index++;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	if (data->index > 2192)
		return (FAIL);
	return(SUCCESS);
}

int		encode_multi_comment(t_parser *data)
{
	data->bytecode[data->index] = 0x0a;
	ft_strdel(&data->line);
	while (get_next_line(data->fd, &data->line ) > 0 
			&& ft_strchr(data->line, '\"') == NULL)
	{
		if (!(encode_comment(data, 0)))
			return(FAIL);
		ft_strdel(&data->line);
		data->bytecode[data->index] = 0x0a;
	}
	if (!(encode_comment(data, 0)))
		return(FAIL);
	return (SUCCESS);
}

void	encode_name(t_parser *data, int i)
{
	data->bytecode[data->index++] = 0;
	data->bytecode[data->index++] = (char)234;
	data->bytecode[data->index++] = (char)131;
	data->bytecode[data->index++] = (char)243;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	while (data->index < 139)
		data->bytecode[data->index++] = 0;
}

int		encode_header(t_parser *data, int i)
{
	if (ft_strccmp(".name", &data->line[i]) == IDENTICAL)
	{
		i += 5;
		i += ft_strspn(&data->line[i], " \t") + 1;
		if (ft_strlen_c(&data->line[i], '"') > 128)
		{
			ft_printf("ERROR_NAME_LEN\n");
			return (-1);
		}
		encode_name(data, i);
	}
	else if (ft_strccmp(".comment", &data->line[i]) == IDENTICAL)
	{
		i += 8;
		i += ft_strlen_c(&data->line[i], '"') + 1;
		if (!(encode_comment(data, i)))
			return (FAIL);
		if (ft_strchr(&data->line[i], '\"') == NULL)
			if (!(encode_multi_comment(data)))
				return (FAIL);
		while (data->index < 2192)
			data->bytecode[data->index++] = 0;
	}
	return (SUCCESS);
}
