/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:59:55 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/07/29 19:00:19 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

WINDOW			*protect_dupwin(t_env *env, WINDOW *to_dup)
{
	WINDOW	*dup;

	if (!(dup = dupwin(to_dup)))
		exit_clean(env);
	return (dup);
}

static void		overwrite_trace(t_env *env)
{
	overlay(env->mem, env->trace[env->cycle_index % GO_BACK]);
	if (env->option == 1)
		overwrite(env->infos,
				env->traceinfos[env->cycle_index % GO_BACK]);
	if (env->option == 1 && env->verb == 1)
		overwrite(env->verbos,
				env->traceverbos[env->cycle_index % GO_BACK]);
}

void			read_memory_visu(t_env *env)
{
	if (env->option == 1)
		print_infos(env);
	protect_wrefresh(env, env->mem);
	if (env->goback == 1)
	{
		if (env->cycle_index > GO_BACK)
			overwrite_trace(env);
		else
		{
			env->trace[env->cycle_index % GO_BACK] =\
											protect_dupwin(env, env->mem);
			if (env->option == 1)
				env->traceinfos[env->cycle_index % GO_BACK] =\
											protect_dupwin(env, env->infos);
			if (env->option == 1 && env->verb == 1)
				env->traceverbos[env->cycle_index % GO_BACK] =\
											protect_dupwin(env, env->verbos);
		}
	}
	key_events(env);
}
