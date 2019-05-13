/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/05/14 01:07:16 by sabri            ###   ########.fr       */
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

int		save_label_address(char *line)
{
	(void)line;
	ft_printf("save_label_address\n");
	return (1);
}

int		choose_instruction(t_parser *data, int i)
{
	if (ft_strccmp("sti", &data->line[i]) == IDENTICAL)
		return (ft_encode_sti(data));
	if (ft_strccmp("sub", &data->line[i]) == IDENTICAL)
		return (ft_encode_sub(data));
	if (ft_strccmp("and", &data->line[i]) == IDENTICAL)
		return (ft_encode_and(data));
	if (ft_strccmp("or", &data->line[i]) == IDENTICAL)
		return (ft_encode_or(data));
	if (ft_strccmp("xor", &data->line[i]) == IDENTICAL)
		return (ft_encode_xor(data));
	if (ft_strccmp("zjmp", &data->line[i]) == IDENTICAL)
		return (ft_encode_zjmp(data));
	if (ft_strccmp("ldi", &data->line[i]) == IDENTICAL)
		return (ft_encode_ldi(data));
	if (ft_strccmp("fork", &data->line[i]) == IDENTICAL)
		return (ft_encode_fork(data));
	if (ft_strccmp("live", &data->line[i]) == IDENTICAL)
		return (ft_encode_live(data));
	if (ft_strccmp("ld", &data->line[i]) == IDENTICAL)
		return (ft_encode_ld(data));
	if (ft_strccmp("st", &data->line[i]) == IDENTICAL)
		return (ft_encode_st(data));
	if (ft_strccmp("add", &data->line[i]) == IDENTICAL)
		return (ft_encode_add(data));
	return (0);
}


int		main(int ac, char **av)
{
	t_parser	*data;
	int	i;
	int	label_flag;

	if (ac == 2)
	{
		if (!(data = parser_init()))
			return (clean_quit(NULL, 1));
		if (safe_open(av[1], data, O_RDONLY) == FAIL)
			return (clean_quit(&data, 1));
		while (get_next_line(data->fd, &data->line) > 0)
		{
			ft_printf("READ>>{%s}\n", data->line);
			i = ft_strspn(data->line, " \t");
			label_flag = 0;
			while (data->line[i])
			{
				if (data->line[i] == '.')
				{
					ft_printf("line_name/comment\n", data->line);
					break ;
				}
				else if (data->line[i] == ':') 
					label_flag = save_label_address(data->line);
				else if (data->line[i] == ' ' || data->line[i] == '\t')
				{
					if (label_flag == 0)
						i = 0;
					i += ft_strspn(&data->line[i], " \t");
					if (choose_instruction(data, i) == -1)
					{
						ft_printf("ERROR\n");
						return (clean_quit(&data, 1));
					}
					break ;
				}
				i++;
			}
			ft_strdel(&data->line);
			ft_printf("END_READ\n\n");
		}
		ft_printf("\n>>>>BYTECODE<<<<\n%i\n", data->index);
		write(1, data->bytecode, data->index);
		close(data->fd);
		ft_write_cor(data, av[1]);
	//	clean_quit(&data, 0);

	}
	return (0);
}
