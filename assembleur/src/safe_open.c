/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:48 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 21:54:12 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static int	check_pathname(const char *pathname)
{
	char	*tmp;

	tmp = ft_strstr(pathname, EXTENSION);
	if (tmp == NULL)
		return (FAIL);
	if (ft_strlen(tmp) != 2)
		return (FAIL);
	return (SUCCESS);
}

int			safe_open(const char *pathname, t_parser *data, const int flags,
				const int check_ext)
{
	int		fd;

	if (check_ext == 1)
		if (check_pathname(pathname) == FAIL)
		{
			data->err_code = 14;
			data->err_msg = "Wrong file extension ";
			return (FAIL);
		}
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
