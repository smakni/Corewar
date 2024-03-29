/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_validity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:45:38 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	ft_check_args_validity(char **argv, t_env *env)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strstr(argv[i], CHAMP_EXTENSION))
			return (SUCCESS);
		i++;
	}
	env->err_code = 2;
	env->err_msg = "Can't read source file";
	return (FAIL);
}
