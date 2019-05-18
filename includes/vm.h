/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:10:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/17 16:54:38 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define MAX_CHAMP_CODE_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define FAIL		0
# define SUCCESS	1

typedef struct	s_champ
{
	char		*name;
	int			player_nb;
}				t_champ;

typedef struct	s_env
{
	t_champ				champ[4];
	char				*err_msg;
	int					err_code;
	int					fd;
	int					dump;
	int					nb_champs;
	unsigned char		memory[4096];
}				t_env;

void			ft_parse_argc(int argc, char **argv, t_env *env);
void			write_champ(t_env *env);
int				read_multi_bytes(unsigned char *line, int index, int nb_bytes);
int				safe_open(const char *pathname, t_env *data, const int flags);

#endif
