/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:41:43 by smakni            #+#    #+#             */
/*   Updated: 2019/05/16 15:02:10 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

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

static int		encode_comment(t_parser *data, int i)
{
	data->index++;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	if (data->index > 0x890)
		return (FAIL);
	return(SUCCESS);
}

int		encode_multi_name(t_parser *data)
{
	data->bytecode[data->index] = 0x0a;
	ft_strdel(&data->line);
	while (get_next_line(data->fd, &data->line, &data->eol) > 0 
			&& ft_strchr(data->line, '\"') == NULL)
	{
		if (!(encode_name(data, 0)))
			return(FAIL);
		ft_strdel(&data->line);
		data->bytecode[data->index] = 0x0a;
		data->nb_line++;
	}
	if (!(encode_name(data, 0)))
		return(FAIL);
	data->nb_line++;
	return (SUCCESS);
}

int		encode_multi_comment(t_parser *data)
{
	data->bytecode[data->index] = 0x0a;
	ft_strdel(&data->line);
	while (get_next_line(data->fd, &data->line, &data->eol) > 0 
			&& ft_strchr(data->line, '\"') == NULL)
	{
		if (!(encode_comment(data, 0)))
			return(FAIL);
		ft_strdel(&data->line);
		data->bytecode[data->index] = 0x0a;
		data->nb_line++;
	}
	if (!(encode_comment(data, 0)))
		return(FAIL);
	data->nb_line++;
	return (SUCCESS);
}

int		encode_header(t_parser *data, int i)
{
	if (ft_strncmp(".name", &data->line[i], 5) == IDENTICAL)
	{
		data->index = 0;
		data->bytecode[data->index++] = 0;
		data->bytecode[data->index++] = (char)234;
		data->bytecode[data->index++] = (char)131;
		data->bytecode[data->index] = (char)243;
		if (data->line[i + 5] != '\t' && data->line[i + 5] != ' ' && data->line[i + 5] != '"')
			return (FAIL);
		i += 5;
		i += ft_strspn(&data->line[i], " \t") + 1;
		if (!(encode_name(data, i)))
			return (FAIL);
		if (ft_strchr(&data->line[i], '\"') == NULL)
			if (!(encode_multi_name(data)))
				return (FAIL);
		while (data->index < 0x8b)
			data->bytecode[data->index++] = 0;
		data->index = 0x890;
	}
	else if (ft_strncmp(".comment", &data->line[i], 8) == IDENTICAL)
	{
		if (data->line[i + 8] != '\t' && data->line[i + 8] != ' ' && data->line[i + 8] != '"')
			return (FAIL);
		i += 8;
		i += ft_strlen_c(&data->line[i], '"') + 1;
		data->index = 0x8b;
		if (!(encode_comment(data, i)))
			return (FAIL);
		if (ft_strchr(&data->line[i], '\"') == NULL)
			if (!(encode_multi_comment(data)))
				return (FAIL);
		while (data->index < 0x890)
			data->bytecode[data->index++] = 0;
	}
	return (SUCCESS);
}
