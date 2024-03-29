/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:12:43 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_indirect_label(char *param, t_parser *data, int i, int is_index)
{
	i = ft_memorize_blank_label(param, data, is_index);
	ft_strdel(&param);
	return (i);
}

static void	set_err_msg(t_parser *data)
{
	data->err_code = 4;
	data->err_msg = "Invalid parameter near line ";
}

int			ft_encode_param(const char *rough_param, const int type_param,
				t_parser *data, int is_index)
{
	int		i;
	char	*param;

	i = 0;
	if (!(param = ft_strtrim(rough_param)))
		return (FAIL);
	if (T_REG & type_param)
		if (param[0] == 'r')
			return (ft_encode_register(param, data));
	if (T_DIR & type_param)
		if (param[0] == '%')
			return (ft_encode_direct(param, data, is_index));
	if (T_IND & type_param)
	{
		if (param[i] == '-')
			i++;
		if (ft_str_is_numeric(&param[i]))
			return (ft_encode_indirect(param, data));
		if (param[0] == ':')
			return (ft_indirect_label(param, data, i, is_index));
	}
	ft_strdel(&param);
	set_err_msg(data);
	return (FAIL);
}
