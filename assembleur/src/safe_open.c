/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:48 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/29 16:11:50 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	safe_read(const int fd, t_parser *data)
{
	if (read(fd, 0, 0) < 0)
	{
		data->err_code = 3;
		data->err_msg = "Syntax error near line ";
		return (FAIL);
	}
	return (SUCCESS);
}

int			safe_open(const char *pathname, t_parser *data, const int flags)
{
	int		fd;

	fd = open(pathname, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		data->err_code = 1;
		data->err_msg = "Can't read source file ";
		return (FAIL);
	}
	if (!(flags & O_CREAT))
		if (!(safe_read(fd, data)))
			return (FAIL);
	data->fd = fd;
	return (SUCCESS);
}
