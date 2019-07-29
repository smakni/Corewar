/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:19:53 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 21:37:59 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_encode_lfork(t_parser *data)
{
	int	i;

	data->bytecode[data->index] = 15;
	data->index++;
	i = ft_strspn(data->line, " \t") + 5;
	i += ft_strspn(&data->line[i], " \t");
	if (ft_strchr(&data->line[i], ','))
		return (FAIL);
	if (!(ft_encode_param(&data->line[i], T_DIR, data, 1)))
		return (FAIL);
	return (SUCCESS);
}
