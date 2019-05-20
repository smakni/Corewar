/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 22:51:17 by sabri             #+#    #+#             */
/*   Updated: 2019/05/21 00:34:36 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/vm.h"

void		op_fork(t_env *env, t_fork **fork, int j)
{
	int		i;
	t_fork	*tmp;
	t_fork	*new;

	i = 0;
	tmp = *fork;
	if (!(new = ft_memalloc(sizeof(t_fork))))
		exit (-1);
	new->champ_cpy = env->champ[j];
	new->next = NULL;
	if (*fork == NULL)
	{
		*fork = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp = *fork;
	while (tmp->next != NULL)
	{
		ft_printf("fork_name[%d]= %s\n", i, tmp->champ_cpy.header.prog_name);
		i++;
		tmp = tmp->next;
	}

}