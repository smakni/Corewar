/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 20:17:25 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 20:31:35 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		**split_args(t_parser *data, const char *str, const int arg_required)
{
	char	**ret;

	if (count(str, ',') != arg_required - 1)
	{
		data->err_code = 3;
		data->err_msg = "Syntax error near line ";
		return (NULL);
	}
	if (!(ret = ft_strsplit(str, ',')))
	{
		data->err_code = 15;
		data->err_msg = "Failed to malloc";
		return (NULL);
	}
	if (ft_arrlen((void*)ret) != (size_t)arg_required)
	{
		data->err_code = 3;
		data->err_msg = "Syntax error near line ";
		ft_tabdel((void*)ret, ft_arrlen((void*)ret));
		return (NULL);
	}
	return (ret);
}