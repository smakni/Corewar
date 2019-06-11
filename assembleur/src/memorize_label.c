/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorize_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:06:39 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/11 22:18:27 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	clean_quit(t_bytes *elem, char *param, const int free_asked, const int ret)
{
	if (free_asked == 1)
		ft_strdel(&param);
	ft_strdel(&elem->label);
	ft_memdel((void*)&elem);
	return (ret);
}

static void	increment_values(const char *param, t_bytes *elem, t_parser *data,
				const int is_index)
{
	if (is_index || param[0] == ':')
	{
		elem->size = 2;
		data->index += 2;
	}
	else
	{
		elem->size = 4;
		data->index += 4;
	}
}

int			ft_memorize_blank_label(const char *param, t_parser *data,
				const int is_index, const int free_asked)
{
	t_bytes	*elem;
	int		i;

	if (!(elem = bytes_init(data)))
		return (FAIL);
	i = ft_strlen_c(param, ':') + 1;
	if (!(elem->label = ft_strdup(&param[i])))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc";
		return (FAIL);
	}
	if (!(check_label_chars(elem->label, data)))
		return (clean_quit(elem, (char*)param, free_asked, FAIL));
	elem->index = data->index;
	elem->index_instruction = data->index_instruction;
	increment_values(param, elem, data, is_index);
	ft_add_byte_elem(&data->blanks, elem);
	return (clean_quit(elem, (char*)param, free_asked, SUCCESS));
}
