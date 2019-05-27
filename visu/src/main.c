/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:00:09 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/05/27 11:30:38 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <strings.h>
#include <stdlib.h>

int main(void)
{
	WINDOW	*around_memory;
	WINDOW	*memory;
	WINDOW	*infos;
	char	*str;
	int		i;

	str = malloc(4097);
	initscr();
	while (1)
	{
		wclear(memory);
		start_color();
		init_color(COLOR_CYAN, 460, 460, 460);
		init_color(COLOR_MAGENTA, 520, 520, 520);
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		attron(A_REVERSE | A_STANDOUT);
		around_memory = subwin(stdscr, 68, 197, 0, 0);
		wborder(around_memory, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		infos = subwin(stdscr, 68, 58, 0, 196);
		wborder(infos, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		attroff(A_REVERSE | A_STANDOUT);
		attron(COLOR_PAIR(1));
		memory = subwin(stdscr, 64, 193, 2, 3);
		i = 0;
		while (i < 4096)
		{
			wprintw(memory, "%.2x", str[i]);
			wprintw(memory, " ");
			i++;
			if (i % 64 == 0)
				wprintw(memory, "\n");
			
		}
		refresh();
		getch();
	}
	delwin(memory);
	delwin(infos);
	endwin();
	return (0);
}