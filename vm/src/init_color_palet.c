/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_palet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:57:52 by jergauth          #+#    #+#             */
/*   Updated: 2019/06/27 12:10:59 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <curses.h>

static int	pair_colors_to_black(int *n)
{
	int	color_defined;

	color_defined = 1;
	while (*n < 8)
	{
		if (init_pair(*n, color_defined, COLOR_BLACK) == ERR)
			return (ERR);
		color_defined++;
		(*n)++;
	}
	return (SUCCESS);
}

static int	pair_black_to_colors(int *n)
{
	int	color_defined;

	color_defined = 1;
	while (*n < 12)
	{
		if (init_pair(*n, COLOR_BLACK, color_defined) == ERR)
			return (ERR);
		color_defined++;
		(*n)++;
	}
	if (init_pair(*n, COLOR_BLACK, COLOR_CYAN) == ERR)
		return (ERR);
	(*n)++;
	return (SUCCESS);
}

static int	pair_white_to_colors(int *n)
{
	int	color_defined;

	color_defined = 1;
	while (*n < 17)
	{
		if (init_pair(*n, COLOR_WHITE, color_defined) == ERR)
			return (ERR);
		color_defined++;
		(*n)++;
	}
	return (SUCCESS);
}

int			init_color_palet(void)
{
	int	n;

	if (start_color() == ERR)
		return (ERR);
	if (init_color(COLOR_CYAN, 460, 460, 460) == ERR)
		return (ERR);
	if (init_color(COLOR_MAGENTA, 520, 520, 520) == ERR)
		return (ERR);
	if (init_color(COLOR_WHITE, 1000, 1000, 1000) == ERR)
		return (ERR);
	n = 1;
	if (pair_colors_to_black(&n) == ERR)
		return (ERR);
	if (pair_black_to_colors(&n) == ERR)
		return (ERR);
	if (pair_white_to_colors(&n) == ERR)
		return (ERR);
	return (SUCCESS);
}
