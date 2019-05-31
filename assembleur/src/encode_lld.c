/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:19:41 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/30 20:49:05 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		clean_quit(void **params, const int ret)
{
	ft_tabdel(params, ft_arrlen(params));
	return (ret);
}

int				ft_encode_lld(t_parser *data)
{
	int		i;
	char	**params;

	data->bytecode[data->index] = 13;
	data->index++;
	i = ft_strspn(data->line, " \t") + 3;
	i += ft_strspn(&data->line[i], " \t");
	if (!(params = ft_strsplit(&data->line[i], ',')))
		return (FAIL);
	if (ft_arrlen((void*)params) != 2)
	{
		data->err_code = 3;
		data->err_msg = "Syntax error near line ";
		return (clean_quit((void*)params, FAIL));
	}
	if (!(ft_parse_args(data, params)))
		return (clean_quit((void*)params, FAIL));
	if (!(ft_encode_param(params[0], T_DIR | T_IND, data, 0)))
		return (clean_quit((void*)params, FAIL));
	if (!(ft_encode_param(params[1], T_REG, data, 0)))
		return (clean_quit((void*)params, FAIL));
	return (clean_quit((void*)params, SUCCESS));
}
