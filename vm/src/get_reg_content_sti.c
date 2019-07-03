/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reg_content_sti.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:26:33 by jergauth          #+#    #+#             */
/*   Updated: 2019/07/03 10:30:27 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		get_reg_content_arg3(t_env *env, unsigned int j, int *cursor,
			int *nb_reg)
{
	int	content;

	content = 0;
	*nb_reg = env->process[j].op.saved[*cursor];
	if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
		content = env->process[j].r[*nb_reg];
	if (*cursor > 2)
		if (env->verb == 1)
			save_ind_param(env, j, content, 2);
	(*cursor)++;
	return (content);
}

int		get_reg_content_arg2(t_env *env, unsigned int j, int *cursor,
			int *nb_reg)
{
	int	content;

	content = 0;
	*nb_reg = env->process[j].op.saved[*cursor];
	if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
		content = env->process[j].r[*nb_reg];
	if (*cursor > 2)
		if (env->verb == 1)
			save_ind_param(env, j, content, 1);
	(*cursor)++;
	return (content);
}

int		get_reg_content_arg1(t_env *env, unsigned int j, int *cursor,
			int *nb_reg)
{
	int	content;

	content = 0;
	*nb_reg = env->process[j].op.saved[*cursor];
	if (*nb_reg >= 1 && *nb_reg <= REG_NUMBER)
		content = env->process[j].r[*nb_reg];
	if (*cursor > 2)
		if (env->verb == 1)
			save_ind_param(env, j, content, 0);
	(*cursor)++;
	return (content);
}
