/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:24:29 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:24:31 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_level_count(t_btree *root)
{
	int		left;
	int		right;

	if (root == NULL)
		return (0);
	left = btree_level_count(root->left);
	right = btree_level_count(root->right);
	if (left > right)
		return (left + 1);
	return (right + 1);
}
