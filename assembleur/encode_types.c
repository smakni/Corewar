/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:13:38 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:59:11 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	clean_quit(t_parser *data, char **param, const int ret)
{
	ft_strdel(param);
	if (ret == FAIL)
	{
		data->err_code = 3;
		data->err_msg = "Syntax error near line ";
	}
	return (ret);
}

int			ft_encode_indirect(char *param, t_parser *data)
{
	short nb;

	nb = (short)ft_atoi(param);
	data->bytecode[data->index] = nb >> 8;
	data->bytecode[data->index + 1] = nb;
	data->index += 2;
	return (clean_quit(data, &param, SUCCESS));
}

static void	increment_values(const char *param, t_parser *data,
				const int is_index)
{
	int	nb;

	if (is_index)
	{
		nb = (short)ft_atoi(&param[1]);
		data->bytecode[data->index] = nb >> 8;
		data->bytecode[data->index + 1] = nb;
		data->index += 2;
	}
	else
	{
		nb = ft_atoi(&param[1]);
		data->bytecode[data->index] = nb >> 24;
		data->bytecode[data->index + 1] = nb >> 16;
		data->bytecode[data->index + 2] = nb >> 8;
		data->bytecode[data->index + 3] = nb;
		data->index += 4;
	}
}

int			ft_encode_direct(char *param, t_parser *data, int is_index)
{
	int i;

	i = 1;
	if (ft_strlen(param) <= 1)
		return (clean_quit(data, &param, FAIL));
	if (param[0] == ':' || param[i] == ':')
		ft_memorize_blank_label(param, data, is_index);
	else
	{
		if (param[i] == '-')
			i++;
		if (ft_str_is_numeric(&param[i]) == false)
			return (clean_quit(data, &param, FAIL));
		increment_values(param, data, is_index);
	}
	return (clean_quit(data, &param, SUCCESS));
}

int			ft_encode_register(char *param, t_parser *data)
{
	int		reg_nb;
	size_t	len;

	len = ft_strlen(param);
	if (len <= 1 || len > 3)
		return (clean_quit(data, &param, FAIL));
	if (ft_str_is_numeric(&param[1]) == false)
		return (clean_quit(data, &param, FAIL));
	reg_nb = ft_atoi(&param[1]);
	data->bytecode[data->index] = reg_nb;
	data->index++;
	return (clean_quit(data, &param, SUCCESS));
}
