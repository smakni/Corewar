/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:12:43 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/11 22:18:40 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

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
			return (ft_memorize_blank_label(param, data, is_index, 1));
	}
	ft_strdel(&param);
	data->err_code = 4;
	data->err_msg = "Invalid parameter near line ";
	return (FAIL);
}
