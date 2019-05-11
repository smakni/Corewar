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

#include "../../includes/asm.h"

int		save_label_address(char *line)
{
	ft_printf("save_label_address\n");
	return (1);
}

int		choose_instruction(char *line, int *index)
{
	if (ft_strncmp(line, "live", 4) == 0)
		ft_printf("instruction_live\n");
	else if (ft_strncmp(line, "sti", 3) == 0)
		ft_encode_sti(line, index);
	else if (ft_strncmp(line, "and", 3) == 0)
		ft_printf("instruction_and\n");
	else if (ft_strncmp(line, "add", 3) == 0)
		ft_printf("instruction_add\n");
	else if (ft_strncmp(line, "sub", 3) == 0)
		ft_printf("instruction_sub\n");
	else if (ft_strncmp(line, "or", 2) == 0)
		ft_printf("instruction_or\n");
	else if (ft_strncmp(line, "xor", 3) == 0)
		ft_printf("instruction_xor\n");
	else if (ft_strncmp(line, "zjmp", 3) == 0)
		ft_printf("instruction_zjmp\n");
	else if (ft_strncmp(line, "ldi", 3) == 0)
		ft_printf("instruction_ldi\n");
	else if (ft_strncmp(line, "fork", 4) == 0)
		ft_printf("instruction_fork\n");
	else if (ft_strncmp(line, "lld", 3) == 0)
		ft_printf("instruction_lld\n");
	else if (ft_strncmp(line, "lldi", 4) == 0)
		ft_printf("instruction_lldi\n");
	else if (ft_strncmp(line, "ld", 2) == 0)
		ft_printf("instruction_ld\n");
	else if (ft_strncmp(line, "st", 2) == 0)
		ft_printf("instruction_st\n");
	else if (ft_strncmp(line, "lfork", 4) == 0)
		ft_printf("instruction_fork\n");
	else if (ft_strncmp(line, "aff", 3) == 0)
		ft_printf("instruction_aff\n");
	else
		return (-1);
	return (0);
}

int		jump_initial_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return(i);
}

int		main(int ac, char **av)
{
	char	bytecode[100];
	char	*line;
	int 	fd;
	int	i;
	int	index;
	int	label_flag;

	if (ac == 2)
	{
		index = 0;
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			ft_printf("READ>>{%s}\n", line);
			i = jump_initial_spaces(line);
			label_flag = 0;
			while (line[i])
			{
				if (line[i] == '.')
				{
					ft_printf("line_name/comment\n", line);
					break ;
				}
				else if (line[i] == ':') 
					label_flag = save_label_address(line);
				else if (line[i] == ' ' || line[i] == '\t')
				{
					if (label_flag == 0)
						i = 0;
					i += jump_initial_spaces(&line[i]);
					if (choose_instruction(&line[i], &index) == -1)
					{
						ft_printf("ERROR\n");
						exit (-1);
					}
					break ;
				}
				i++;
			}
			free(line);
			ft_printf("END_READ\n\n");
		}
		ft_printf("\n>>>>BYTECODE<<<<\n");
		write(0, bytecode, 100);
	}
	return (0);
}
