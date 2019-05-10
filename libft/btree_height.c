/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_height.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:24:16 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:24:17 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_height(t_btree *root)
{
	int	lh;
	int	rh;

	if (root == NULL)
		return (0);
	if (root->left == NULL)
		lh = 0;
	else
		lh = 1 + root->left->height;
	if (root->right == NULL)
		rh = 0;
	else
		rh = 1 + root->right->height;
	if (lh > rh)
		return (lh);
	return (rh);
}
