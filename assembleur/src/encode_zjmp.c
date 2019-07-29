/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:12:23 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_encode_zjmp(t_parser *data)
{
	int		i;

	data->bytecode[data->index] = 9;
	data->index++;
	i = ft_strspn(data->line, " \t") + 4;
	i += ft_strspn(&data->line[i], " \t");
	if (!(ft_encode_param(&data->line[i], T_DIR, data, 1)))
		return (FAIL);
	return (SUCCESS);
}
