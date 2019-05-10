/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_balance_factor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:23:27 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:23:28 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_balance_factor(t_btree *root)
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
	return (lh - rh);
}
