/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix_lr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:23:06 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:23:07 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix_lr(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root->data)
			applyf(root->data);
		if (root->left)
			btree_apply_prefix_lr(root->left, applyf);
		if (root->right)
			btree_apply_prefix_lr(root->right, applyf);
	}
}
