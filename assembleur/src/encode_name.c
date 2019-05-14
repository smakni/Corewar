/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:41:43 by smakni            #+#    #+#             */
/*   Updated: 2019/05/14 19:25:43 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int 	ft_strlen_c(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	encode_name(t_parser *data, int i)
{
	data->bytecode[data->index++] = 0;
	data->bytecode[data->index++] = (char)234;
	data->bytecode[data->index++] = (char)131;
	data->bytecode[data->index++] = (char)243;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	while (data->index < 139)
		data->bytecode[data->index++] = 0;
}

void	encode_comment(t_parser *data, int i)
{
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		i++;
		data->index++;
	}
	while (data->index < 2048)
		data->bytecode[data->index++] = 0;
}

int		encode_header(t_parser *data, int i)
{
	if (ft_strccmp(".name", &data->line[i]) == IDENTICAL)
	{
		i += 5;
		i += ft_strspn(&data->line[i], " \t") + 1;
		if (ft_strlen_c(&data->line[i], '"') > 128)
		{
			ft_printf("ERROR_NAME_LEN\n");
			return (-1);
		}
		encode_name(data, i);
	}
	else if (ft_strccmp(".comment", &data->line[i]) == IDENTICAL)
	{
		i += 8;
		i += ft_strspn(&data->line[i], " \t") + 1;
		if (ft_strlen_c(&data->line[i], '"') > 2048)
		{
			ft_printf("ERROR_COMMENT_LEN\n");
			return (-1);
		}
		encode_comment(data, i);
	}
	return (0);
}