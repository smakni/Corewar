/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:48:27 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/02 20:29:49 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		check_label_chars(char *str, t_parser *data)
{
	while (*str && *str != ':')
	{
		if (ft_strchr(LABEL_CHARS, *str) == NULL)
		{
			data->err_code = 8;
			data->err_msg = "Lexical error near line ";
			return (FAIL);
		}
		str++;
	}
	return (SUCCESS);
}

int		save_label_address(t_parser *data)
{
	t_bytes	*elem;
	int		i;

	data->syntax_flag = 1;
	i = ft_strspn(data->line, " \t");
	if (!(&data->line[i]))
		return (FAIL);
	if (!(elem = bytes_init(data)))
		return (FAIL);
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
