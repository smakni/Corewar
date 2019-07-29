/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:41:43 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	encode_magic_number(t_parser *data)
{
	data->index = 0;
	data->bytecode[data->index++] = (char)0x00;
	data->bytecode[data->index++] = (char)0xEA;
	data->bytecode[data->index++] = (char)0x83;
	data->bytecode[data->index] = (char)0xF3;
}

static int	encode_header_name(t_parser *data, int i)
{
	int	nb_chars;

	data->header_name_flag++;
	encode_magic_number(data);
	if (data->line[i + 5] != '\t' && data->line[i + 5] != ' '
			&& data->line[i + 5] != '"')
		return (FAIL);
	i += 5;
	i += ft_strlen_c(&data->line[i], '"') + 1;
	nb_chars = 0;
	if (!(encode_name(data, i, &nb_chars)))
		return (FAIL);
	if (ft_strchr(&data->line[i], '\"') == NULL)
		if (!(encode_multi_name(data, &nb_chars)))
			return (FAIL);
	while (data->index < 0x8b)
		data->bytecode[data->index++] = 0;
	data->index = 0x890;
	return (SUCCESS);
}

static int	encode_header_comment(t_parser *data, int i)
{
	int	nb_chars;

	data->header_comment_flag++;
	if (data->line[i + 8] != '\t' && data->line[i + 8] != ' '
			&& data->line[i + 8] != '"')
		return (FAIL);
	i += 8;
	i += ft_strlen_c(&data->line[i], '"') + 1;
	nb_chars = 0;
	data->index = 0x8b;
	if (!(encode_comment(data, i, &nb_chars)))
		return (FAIL);
	if (ft_strchr(&data->line[i], '\"') == NULL)
		if (!(encode_multi_comment(data, &nb_chars)))
			return (FAIL);
	while (data->index < 0x890)
		data->bytecode[data->index++] = 0;
	return (SUCCESS);
}

int			encode_header(t_parser *data, int i)
{
	data->syntax_flag = 1;
	if (ft_strncmp(NAME_CMD_STRING, &data->line[i], 5) == IDENTICAL)
	{
		if (!(encode_header_name(data, i)))
			return (FAIL);
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, &data->line[i], 8) == IDENTICAL)
	{
		if (!(encode_header_comment(data, i)))
			return (FAIL);
	}
	else
	{
		data->err_code = 8;
		data->err_msg = "Lexical error near line ";
		return (FAIL);
	}
	return (SUCCESS);
}
