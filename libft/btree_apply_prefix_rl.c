/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix_rl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:23:10 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:23:10 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix_rl(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root->data)
			applyf(root->data);
		if (root->right)
			btree_apply_prefix_rl(root->right, applyf);
		if (root->left)
			btree_apply_prefix_rl(root->left, applyf);
	}
}
