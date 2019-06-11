/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:07:10 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/11 21:40:26 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		check_args(t_env *env, unsigned int j, int *cursor, int nb_param)
{
	int	tmp;
	int	mask;
	int	encode_byte;

	mask = 0b00000011;
	encode_byte = env->memory[env->champ[j].pc + *cursor];
	ft_printf("byte %#.8b\n", encode_byte);
	tmp = (4 - nb_param) * 2;
	if ((0b11111111 & (encode_byte << tmp)) != 0)
	{
		// ft_printf("FAIL on non-encoded bits\n");
		return (0);
	}
	while (nb_param > 0)
	{
		// ft_printf("---%i---\n", nb_param);
		tmp = encode_byte >> (8 - nb_param * 2);
			// ft_printf("tmp %#.8b\nmask = %#.8b\n", tmp, mask);
		tmp &= mask;
			// ft_printf("tmp isole %#.8b\n%i | %i = %i\n", tmp, tmp, 0, (tmp | 0x0));
		if ((tmp | 0b00000000) == 0)
		{
			(*cursor)++;
			// ft_printf("FAIL on %i\n", nb_param);
			return (0);
		}
		nb_param--;
	}
	return (1);
}
