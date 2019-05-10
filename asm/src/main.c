/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:05:45 by smakni            #+#    #+#             */
/*   Updated: 2019/05/10 19:00:46 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	save_data(t_data **data, char *line)
{
	t_data *tmp;
	t_data *new;

	if (!(new = ft_memalloc(sizeof(t_data))))
		return ;
	new->line = line;
	new->next = NULL;
	if (*data == NULL)
	{
		*data = new;
		return ;
	}
	tmp = *data;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_free(t_data *data)
{
	t_data *tmp;

	while (data->next)
	{
		ft_printf("%s\n", data->line);
		tmp = data->next;
		free(data->line);
		free(data);
		data = tmp;
	}
	free(data->line);
	free(data);
}

int		main(int ac, char **av)
{
	t_data	*data;
	char	*line;
	int 	fd;
	
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			save_data(&data, line);
		}
		print_free(data);
	}
	return (0);
}
