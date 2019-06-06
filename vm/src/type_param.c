/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <cmoulini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:00:24 by cmoulini          #+#    #+#             */
/*   Updated: 2019/06/06 18:00:24 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int	type_param(unsigned char byte, int param)
{
    char    mask;
    char    tmp;

    mask = 0b00000011;
    tmp = mask & (byte >> ((3 - param + 1) * 2));
    return (tmp);
}
