/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 21:54:17 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	clean_quit(t_parser *data, const int ret)
{
	if (data->err_code > 0)
	{
		ft_dprintf(2, "{red}%s", data->err_msg);
		if (data->err_code == 1 || data->err_code == 14)
			ft_dprintf(2, "%s", data->pathname);
		else if (ft_instr(data->err_code + 48, "3478"))
			ft_dprintf(2, "%i", data->nb_line);
		ft_dprintf(2, ".\n{reset}");
	}
	close(data->fd);
	exit(ret);
}

int			main(int ac, char **av)
{
	t_parser	data;

	if (ac == 2)
	{
		if (!(parser_init(&data, av[1])))
			clean_quit(NULL, EXIT_FAILURE);
		if (safe_open(av[1], &data, O_RDONLY, 1) == FAIL)
			clean_quit(&data, EXIT_FAILURE);
		if (!(reader(&data)))
			clean_quit(&data, EXIT_FAILURE);
		close(data.fd);
		if (!ft_fill_addr(&data))
			clean_quit(&data, EXIT_FAILURE);
		write_prog_size(&data);
		if (!(ft_write_cor(&data, av[1])))
			clean_quit(&data, EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
