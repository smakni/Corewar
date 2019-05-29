/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_byte_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:20:46 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/29 16:20:46 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		ft_encode_byte_param(const char *param)
{
	char	*trimmed;
	int		i;

	i = ft_strspn(param, " \t");
	if (param[i] == 'r')
		return (REG_CODE);
	if (param[i] == '%')
		return (DIR_CODE);
	if (!(trimmed = ft_strtrim(param)))
		return (FAIL);
	i = 0;
	if (trimmed[i] == '-')
		i++;
	if (ft_str_is_numeric(&trimmed[i]) || trimmed[0] == ':')
	{
		ft_strdel(&trimmed);
		return (IND_CODE);
	}
	ft_strdel(&trimmed);
	return (FAIL);
}
