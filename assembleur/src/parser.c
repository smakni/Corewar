/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:55:20 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/03 09:44:55 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	verbose_exit(t_parser *data)
{
	if (ft_instr(data->err_code + 48, "3478"))
		ft_printf("{red}%s%i.{reset}\n", data->err_msg, data->nb_line);
	else
		ft_printf("{red}%s{reset}\n", data->err_msg);
	exit(EXIT_FAILURE);
}

static int	line_parser_extension(t_parser *data, int *i, int *label_flag)
{
	if (data->line[*i] == '.')
	{
		if (!(encode_header(data, *i)))
			return (FAIL);
		return (2);
	}
	else if (data->line[*i] == ':' && *label_flag == 0)
	{
		*label_flag = *i + 1;
		if (!(save_label_address(data)))
			return (FAIL);
	}
	else if (data->line[*i] == ' ' || data->line[*i] == '\t'
		|| data->line[*i] == '%' || data->line[*i] == ':')
	{
		*i = (*label_flag == 0) ? 0 : *label_flag;
		*i += ft_strspn(&data->line[*i], " \t");
		if (data->line[*i] && !ft_instr(data->line[*i], " \t;#"))
		{
			if (!(choose_encoding(data, *i)))
				return (FAIL);
		}
		return (2);
	}
	return (SUCCESS);
}

int			line_parser(t_parser *data, int i, int label_flag)
{
	int	ret;

	data->syntax_flag = 0;
	while (data->line[i])
	{
		if (data->line[i] == '#' || data->line[i] == ';')
			return (SUCCESS);
		else
		{
			ret = line_parser_extension(data, &i, &label_flag);
			if (ret == 2)
				break ;
			else if (ret == FAIL)
				return (FAIL);
		}
		i++;
	}
	if (data->syntax_flag == 0 && ft_strspn(data->line, " \t") != (size_t)i)
	{
		data->err_code = 4;
		data->err_msg = "Syntax error near line ";
		return (FAIL);
	}
	return (SUCCESS);
}

static int	reader_extension(t_parser *data, const int ret)
{
	if (ret == -1)
	{
		data->err_code = 4;
		data->err_msg = "Syntax error near line ";
		return (FAIL);
	}
	if (data->header_name_flag != 1 || data->header_comment_flag != 1)
	{
		data->err_code = 9;
		data->err_msg = "Wrong Name and/or Comment";
		return (FAIL);
	}
	return (SUCCESS);
}

int			reader(t_parser *data)
{
	int i;
	int label_flag;
	int	ret;

	while ((ret = get_next_line(data->fd, &data->line, &data->eol)) > 0)
	{
		if (data->index >= SIZE_BUFFER * data->nb_realloc - 10)
			if (!(ft_realloc_bytecode(data)))
				verbose_exit(data);
		i = ft_strspn(data->line, " \t");
		label_flag = 0;
		if (data->eol == 1 && data->line[i] != '\0'
				&& data->line[i] != '#' && data->line[i] != ';')
		{
			data->err_code = 5;
			data->err_msg = "Syntax error - unexpected end of input";
			verbose_exit(data);
		}
		if (!(line_parser(data, i, label_flag)))
			verbose_exit(data);
		ft_strdel(&data->line);
		data->nb_line++;
	}
	return (reader_extension(data, ret));
}
