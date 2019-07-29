/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_encoding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:21:10 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 18:58:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	choose_encoding_suite(t_parser *data)
{
	if (ft_strccmp("sti", data->line) == IDENTICAL)
		return (ft_encode_sti(data));
	if (ft_strccmp("fork", data->line) == IDENTICAL)
		return (ft_encode_fork(data));
	if (ft_strccmp("lld", data->line) == IDENTICAL)
		return (ft_encode_lld(data));
	if (ft_strccmp("lldi", data->line) == IDENTICAL)
		return (ft_encode_lldi(data));
	if (ft_strccmp("lfork", data->line) == IDENTICAL)
		return (ft_encode_lfork(data));
	if (ft_strccmp("aff", data->line) == IDENTICAL)
		return (ft_encode_aff(data));
	data->err_code = 7;
	data->err_msg = "Invalid instruction near line ";
	return (FAIL);
}

int			choose_encoding(t_parser *data, int i)
{
	data->syntax_flag = 1;
	if (!(ft_format_line(data, i)))
		return (FAIL);
	if (ft_strccmp("live", data->line) == IDENTICAL)
		return (ft_encode_live(data));
	if (ft_strccmp("ld", data->line) == IDENTICAL)
		return (ft_encode_ld(data));
	if (ft_strccmp("st", data->line) == IDENTICAL)
		return (ft_encode_st(data));
	if (ft_strccmp("add", data->line) == IDENTICAL)
		return (ft_encode_add(data));
	if (ft_strccmp("sub", data->line) == IDENTICAL)
		return (ft_encode_sub(data));
	if (ft_strccmp("and", data->line) == IDENTICAL)
		return (ft_encode_and(data));
	if (ft_strccmp("or", data->line) == IDENTICAL)
		return (ft_encode_or(data));
	if (ft_strccmp("xor", data->line) == IDENTICAL)
		return (ft_encode_xor(data));
	if (ft_strccmp("zjmp", data->line) == IDENTICAL)
		return (ft_encode_zjmp(data));
	if (ft_strccmp("ldi", data->line) == IDENTICAL)
		return (ft_encode_ldi(data));
	return (choose_encoding_suite(data));
}
