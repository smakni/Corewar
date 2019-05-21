/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:10:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/21 17:32:30 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define MAX_CHAMP_CODE_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define FAIL		0
# define SUCCESS	1
# define ARR_SIZE	1024

typedef struct	s_champ
{
	unsigned	player_nb;
	header_t	header;
	int			r[REG_NUMBER];
	char		carry;
	unsigned	pc;
	char		cycles;
	int			lives;
}				t_champ;

typedef struct	s_env
{
	unsigned char		memory[MEM_SIZE];
	t_champ				*champ;
	char				*err_msg;
	int					err_code;
	int					fd;
	int					dump;
	int					nb_champs;
	int					nb_realloc;
	int					champ_live[4];
}				t_env;

void			ft_parse_argc(int argc, char **argv, t_env *env);
void			write_champ(t_env *env);
int				read_memory(t_env *env);
int				read_multi_bytes(unsigned char *line, int index, int nb_bytes);
int				safe_open(const char *pathname, t_env *data, const int flags);
int				type_param(unsigned char byte, int param);
int				get_value(t_env *env, int j, int *cursor, int param);
int				get_value_index(t_env *env, int j, int *cursor, int param);
int				exec_op(t_env *env, int j);
void			op_live(t_env *env, int j);
void			op_sti(t_env *env, int j);
void			op_ld(t_env *env, int j);
void			op_st(t_env *env ,int j);
void			op_add(t_env *env ,int j);
void			op_sub(t_env *env ,int j);
void			op_and(t_env *env ,int j);
void			op_or(t_env *env, int j);
void			op_xor(t_env *env, int j);
int				op_fork(t_env *env, int j);
void			op_zjmp(t_env *env, int j);
int				check_cycles(t_env *env, int j);
void			op_ldi(t_env *env ,int j);
void			op_lldi(t_env *env ,int j);

// DEBUG
void	ft_print_memory(t_env *env);

#endif
