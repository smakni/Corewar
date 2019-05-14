/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/05/14 19:33:04 by smakni           ###   ########.fr       */
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
		ft_printf("{red}%s{reset}\n", (*data)->err_msg);
	ft_strdel(&(*data)->line);
	ft_memdel((void*)data);
	return (ret);
}

int		save_label_address(t_parser *data)
{
	t_bytes	*elem;

	if (!(elem = bytes_init(data)))
		return (FAIL);
	if (!(elem->label = ft_strcdup(data->line, ':')))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc a char*";
		return (FAIL);
	}
	elem->index = data->index;
	ft_add_byte_elem(&data->labels, elem);
	return (SUCCESS);
}

void	line_parser(t_parser *data, int i, int label_flag)
{
	while (data->line[i])
	{
		if (data->line[i] == '.')
		{
			encode_header(data, i);
			break ;
		}
		else if (data->line[i] == ':') 
			label_flag = save_label_address(data);
		else if (data->line[i] == ' ' || data->line[i] == '\t')
		{
			if (label_flag == 0)
				i = 0;
			i += ft_strspn(&data->line[i], " \t");
			if (choose_encoding(data, i) == -1)
				ft_printf("ERROR\n");
			break ;
		}
		i++;
	}
}

int		reader(t_parser *data)
{
	int i;
	int label_flag;
	
	while (get_next_line(data->fd, &data->line) > 0)
	{
//		ft_printf("READ>>{%s}\n", data->line);
		i = ft_strspn(data->line, " \t");
		label_flag = 0;
		line_parser(data, i, label_flag);
		ft_strdel(&data->line);
	}
	return (SUCCESS);
}

// static int 	print_list(t_bytes *list)
// {
// 	ft_printf("addr list => %p\n", list);
// 	while (list)
// 	{
// 		ft_printf("Label -> %s | %i | %i\n", list->label, list->index, list->size);
// 		list = list->next;
// 	}
// 	return (SUCCESS);
// }

int		main(int ac, char **av)
{
	t_parser	*data;

	data = NULL;
	if (ac == 2)
	{
		if (!(data = parser_init()))
			return (clean_quit(NULL, 1));
		if (safe_open(av[1], data, O_RDONLY) == FAIL)
			return (clean_quit(&data, 1));
		reader(data);
//			ft_printf("END_READ\n\n");
//		ft_printf("\n>>>>BYTECODE<<<<\n%i\n", data->index);
//		write(1, data->bytecode, data->index);
		close(data->fd);
		ft_fill_addr(data);
		data->bytecode[139] = data->index;
		ft_write_cor(data, av[1]);
	}
	return (0);
}
