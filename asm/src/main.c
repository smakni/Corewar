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

int		choose_instruction(char *line)
{
	if (ft_strcmp(line, "live") == 0)
		ft_printf("instruction_live\n");
	else if (ft_strcmp(line, "sti") == 0)
		ft_printf("instruction_sti\n");
	else if (ft_strcmp(line, "and") == 0)
		ft_printf("instruction_and\n");
	else if (ft_strcmp(line, "sub") == 0)
		ft_printf("instruction_sub\n");
	else if (ft_strcmp(line, "or") == 0)
		ft_printf("instruction_or\n");
	else if (ft_strcmp(line, "xor") == 0)
		ft_printf("instruction_xor\n");
	else if (ft_strcmp(line, "zjmp") == 0)
		ft_printf("instruction_zjmp\n");
	else if (ft_strcmp(line, "ldi") == 0)
		ft_printf("instruction_ldi\n");
	else if (ft_strcmp(line, "fork") == 0)
		ft_printf("instruction_fork\n");
	else if (ft_strcmp(line, "lld") == 0)
		ft_printf("instruction_lld\n");
	else if (ft_strcmp(line, "lldi") == 0)
		ft_printf("instruction_lldi\n");
	else if (ft_strcmp(line, "ld") == 0)
		ft_printf("instruction_ld\n");
	else if (ft_strcmp(line, "st") == 0)
		ft_printf("instruction_st\n");
	else if (ft_strcmp(line, "lfork") == 0)
		ft_printf("instruction_fork\n");
	else if (ft_strcmp(line, "aff") == 0)
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

char	*trim_line(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != c)
		i++;
	return (ft_strsub_free(line, i + 1, ft_strlen(line) - i));
	
}

void	free_tab(char **tab)
{
	int i;
	
	i = 0;
	while(tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

int		main(int ac, char **av)
{
	char	**tab;
	char	*line;
	int 	fd;
	int		i;
	int		label_flag;
	
	if (ac == 2)
	{
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
				else if (line[i] == ':' && label_flag == 0) 
				{
					label_flag = save_label_address(line);
					line = trim_line(line, ':');
					i = 0;
				}
				else if (line[i] == ' ' || line[i] == '\t')
				{
					tab = splitwhitespaces(line);
					if (choose_instruction(tab[0]) == -1)
					{
						ft_printf("ERROR\n");
						exit (-1);
					}
					free_tab(tab);
					break ;
				}
				i++;
			}
			free(line);
			ft_printf("END_READ\n\n");
		}
	}
	return (0);
}
