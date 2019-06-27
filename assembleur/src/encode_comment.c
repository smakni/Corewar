/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:47:19 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/27 10:42:05 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		encode_comment(t_parser *data, int i, int *nb_chars)
{
	data->index++;
	while (data->line[i] && data->line[i] != '\0' && data->line[i] != '"')
	{
		data->bytecode[data->index] = data->line[i];
		(*nb_chars)++;
		i++;
		data->index++;
		if (*nb_chars > COMMENT_LENGTH)
		{
			data->err_code = 10;
			data->err_msg = "Champion comment too long (Max length 2048)";
			return (FAIL);
		}
	}
	if (data->index > 0x890)
		return (FAIL);
	return (SUCCESS);
}

int		encode_multi_comment(t_parser *data, int *nb_chars)
{
	int	ret;

	data->bytecode[data->index] = 0x0a;
	ft_strdel(&data->line);
	while ((ret = get_next_line(data->fd, &data->line, &data->eol)) > 0
				&& ft_strchr(data->line, '\"') == NULL)
	{
		if (!(encode_comment(data, 0, nb_chars)))
			return (FAIL);
		ft_strdel(&data->line);
		data->bytecode[data->index] = 0x0a;
		data->nb_line++;
	}
	if (!(encode_comment(data, 0, nb_chars)) || ret == 0)
	{
		data->err_code = 10;
		data->err_msg = "Bad name and/or comment format";
		return (FAIL);
	}
	data->nb_line++;
	return (SUCCESS);
}
