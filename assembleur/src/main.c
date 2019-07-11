/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/07/11 19:32:58 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	clean_quit(t_parser **data, const int ret)
{
	if (data == NULL)
	{
		ft_printf("{red}Fail to malloc struct s_parser{red}.{reset}\n");
		return (ret);
	}
	if ((*data)->err_code > 0)
	{
		ft_printf("{red}%s", (*data)->err_msg);
		if ((*data)->err_code == 1 || (*data)->err_code == 14)
			ft_printf("%s", (*data)->pathname);
		else if (ft_instr((*data)->err_code + 48, "3478"))
			ft_printf("%i", (*data)->nb_line);
		ft_printf(".\n{reset}");
	}
	ft_bytesdel(&(*data)->labels);
	ft_bytesdel(&(*data)->blanks);
	close((*data)->fd);
	ft_memdel((void*)&(*data)->bytecode);
	ft_strdel(&(*data)->line);
	ft_memdel((void*)data);
	return (ret);
}

int			main(int ac, char **av)
{
	t_parser	*data;

	data = NULL;
	if (ac == 2)
	{
		if (!(data = parser_init(av[1])))
			return (clean_quit(NULL, 1));
		if (safe_open(av[1], data, O_RDONLY, 1) == FAIL)
			return (clean_quit(&data, 1));
		if (!(reader(data)))
			return (clean_quit(&data, 1));
		close(data->fd);
		if (!ft_fill_addr(data))
			return (clean_quit(&data, 1));
		write_prog_size(data);
		if (!(ft_write_cor(data, av[1])))
			return (clean_quit(&data, 1));
		ft_memdel((void*)&data->bytecode);
		ft_strdel(&data->line);
		ft_memdel((void*)&data);
	}
	return (0);
}
