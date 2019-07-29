/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:32:33 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:01:34 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	clean_quit(char **tmp, const int ret)
{
	ft_strdel(tmp);
	return (ret);
}

static int	increment_value(t_parser *data, const char *tmp, int *j)
{
	while (tmp[*j] && tmp[*j + 1])
	{
		if (tmp[*j] == ' ' || tmp[*j] == '\t' || tmp[*j] == '%'
			|| tmp[*j] == ':' || ft_isdigit(tmp[*j]) || tmp[*j] == '-')
			break ;
		if (tmp[*j] == 'r' && ft_isdigit(tmp[*j + 1]))
		{
			data->err_code = 3;
			data->err_msg = "Syntax error near line ";
			return (FAIL);
		}
		(*j)++;
	}
	return (SUCCESS);
}

static char	*insert_space(t_parser *data, char *tmp)
{
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = 0;
	tmp2 = NULL;
	if (!(increment_value(data, tmp, &j)))
		return (NULL);
	if (tmp[j] == '\0' || tmp[j] == ' ' || tmp[j] == '\t')
		return (tmp2);
	if (!(tmp2 = ft_memjoin((void *)tmp, j, (void *)" \0", 2)))
		return (NULL);
	tmp3 = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, &tmp[j])))
	{
		ft_strdel(&tmp3);
		return (NULL);
	}
	ft_strdel(&tmp3);
	return (tmp2);
}

static char	*ft_format_line_extension(t_parser *data, const int i)
{
	char	*tmp;

	if (ft_strrchr(data->line, '#'))
	{
		if (!(tmp = ft_strsub(data->line, i, ft_strlen_c(&data->line[i], '#'))))
			return (NULL);
	}
	else if (ft_strrchr(data->line, ';'))
	{
		if (!(tmp = ft_strsub(data->line, i, ft_strlen_c(&data->line[i], ';'))))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strdup(&data->line[i])))
			return (NULL);
	}
	return (tmp);
}

int			ft_format_line(t_parser *data, int i)
{
	char *tmp;
	char *tmp2;

	data->index_instruction = data->index;
	if (!(tmp = ft_format_line_extension(data, i)))
		return (FAIL);
	tmp2 = insert_space(data, tmp);
	if (data->err_code != 0)
		return (clean_quit(&tmp, FAIL));
	ft_strdel(&data->line);
	data->line = (tmp2 == NULL) ? tmp : tmp2;
	if (tmp2)
		ft_strdel(&tmp);
	return (SUCCESS);
}
