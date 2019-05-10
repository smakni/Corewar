/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:20:42 by jergauth          #+#    #+#             */
/*   Updated: 2018/11/07 11:20:46 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		if (del)
			del((*alst)->content, (*alst)->content_size);
		ft_memdel((void*)&(*alst));
		*alst = tmp;
	}
	*alst = NULL;
}
