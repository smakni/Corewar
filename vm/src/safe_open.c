/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:00:17 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 18:00:17 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static int	safe_read(const int fd, t_env *env)
{
	if (read(fd, 0, 0) < 0)
	{
		env->err_code = 3;
		env->err_msg = "Syntax error near line ";
		return (FAIL);
	}
	return (SUCCESS);
}

int			safe_open(const char *pathname, t_env *env, const int flags)
{
	int		fd;

	fd = open(pathname, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		env->err_code = 1;
		env->err_msg = "Can't read source file ";
		return (FAIL);
	}
	if (!(flags & O_CREAT || flags & O_RDONLY))
		if (!(safe_read(fd, env)))
			return (FAIL);
	env->fd = fd;
	return (SUCCESS);
}
