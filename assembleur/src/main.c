/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/05/16 14:47:10 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	clean_quit(t_parser **data, const int ret)
{
	if (data == NULL)
	{
		ft_printf("{red}Fail to malloc {bold}struct s_parser{reset}{red}.{reset}\n");
		return (ret);
	}
	if ((*data)->err_code > 0)
	{
		ft_printf("{red}%s", (*data)->err_msg);
		if ((*data)->err_code == 1)
			ft_printf("%s", (*data)->pathname);
		else if (ft_instr((*data)->err_code + 48, "3478"))
			ft_printf("%i", (*data)->nb_line);
		ft_printf(".\n{reset}");
	}
	ft_bytesdel(&(*data)->labels);
	ft_bytesdel(&(*data)->blanks);
	close((*data)->fd);
	ft_strdel(&(*data)->line);
	ft_memdel((void*)data);
	return (ret);
}

int		save_label_address(t_parser *data)
{
	t_bytes	*elem;
	int 	i;

	if (!(elem = bytes_init(data)))
		return (FAIL);
	i = ft_strspn(data->line, " \t");
	if (!(elem->label = ft_strcdup(&data->line[i], ':')))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc a char*";
		return (FAIL);
	}
	elem->index = data->index;
	ft_add_byte_elem(&data->labels, elem);
	return (SUCCESS);
}

int		line_parser(t_parser *data, int i, int label_flag)
{
	while (data->line[i])
	{
		if (data->line[i] == '#')
			return (SUCCESS);
		else if (data->line[i] == '.')
		{
			if (!(encode_header(data, i)))
				return (FAIL);
			break ;
		}
		else if (data->line[i] == ':' && label_flag == 0)
		{
			label_flag = i + 1;
			if (!(save_label_address(data)))
				return (FAIL);
		}
		else if (data->line[i] == ' ' || data->line[i] == '\t'
			|| data->line[i] == '%' || data->line[i] == ':')
		{
			if (label_flag == 0)
				i = 0;
			else
				i = label_flag;
			i += ft_strspn(&data->line[i], " \t");
			if (!(choose_encoding(data, i)))
				return (FAIL);
			break ;
		}
		i++;
	}
	return (SUCCESS);
}

int		reader(t_parser *data)
{
	int i;
	int label_flag;
	int	ret;

	while ((ret = get_next_line(data->fd, &data->line, &data->eol)) > 0)
	{
		i = ft_strspn(data->line, " \t");
		label_flag = 0;
		if (data->eol == 1 && data->line[i] != '\0')
		{
			data->err_code = 5;
			data->err_msg = "Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)";
			ft_strdel(&data->line);
			return (FAIL);
		}
		if (!(line_parser(data, i, label_flag)))
			return (FAIL);
		ft_strdel(&data->line);
		data->nb_line++;
	}
	if (ret == -1)
	{
		data->err_code = 4;
		data->err_msg = "Syntax error near line ";
		return (FAIL);
	}
	return (SUCCESS);
}

void	write_prog_size(t_parser *data)
{
	int tmp;

	tmp = data->index - 2192;
	data->bytecode[136] = tmp >> 24;
	data->bytecode[137] = tmp >> 16;
	data->bytecode[138] = tmp >> 8;
	data->bytecode[139] = tmp;
}

int		main(int ac, char **av)
{
	t_parser	*data;

	data = NULL;
	if (ac == 2)
	{
		if (!(data = parser_init(av[1])))
			return (clean_quit(NULL, 1));
		if (safe_open(av[1], data, O_RDONLY) == FAIL)
			return (clean_quit(&data, 1));
		if (!(reader(data)))
			return (clean_quit(&data, 1));
		close(data->fd);
		ft_fill_addr(data);
		write_prog_size(data);
		ft_write_cor(data, av[1]);
		ft_strdel(&data->line);
		ft_memdel((void*)&data);
	}
	return (0);
}
