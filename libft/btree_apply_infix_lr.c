/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix_lr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:51 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:22:52 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_infix_lr(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root->left)
			btree_apply_infix_lr(root->left, applyf);
		if (root->data)
			applyf(root->data);
		if (root->right)
			btree_apply_infix_lr(root->right, applyf);
	}
}
