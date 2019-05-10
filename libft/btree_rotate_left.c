/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_rotate_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:35 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:22:36 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_rotate_left(t_btree **root)
{
	t_btree	*tmp;

	tmp = (*root)->right;
	(*root)->right = tmp->left;
	tmp->left = *root;
	(*root)->height = btree_height(*root);
	tmp->height = btree_height(tmp);
	*root = tmp;
}
