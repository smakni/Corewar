/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_rotate_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:40 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:22:41 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_rotate_right(t_btree **root)
{
	t_btree	*tmp;

	tmp = (*root)->left;
	(*root)->left = tmp->right;
	tmp->right = *root;
	(*root)->height = btree_height(*root);
	tmp->height = btree_height(tmp);
	*root = tmp;
}
