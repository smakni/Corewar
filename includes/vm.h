/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:10:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/22 01:34:59 by sabri            ###   ########.fr       */
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
	header_t	header;
	unsigned	player_nb;
	unsigned	pc;
	int			r[REG_NUMBER];
	int			last_live;
	char		cycles;
	char		last_return;
	char		carry;
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
	int					champ_live[MAX_PLAYERS];
	int					cycle_to_die;
	int					cycle_index;
}				t_env;

void			ft_parse_argc(int argc, char **argv, t_env *env);
void			write_champ(t_env *env);
int				read_memory(t_env *env);
int				read_multi_bytes(unsigned char *line, int index, int nb_bytes);
int				safe_open(const char *pathname, t_env *data, const int flags);
int				type_param(unsigned char byte, int param);
int 			decode_byte_param(unsigned char param, int is_index);
int				get_value(t_env *env, int j, int *cursor, int param);
int				get_value_index(t_env *env, int j, int *cursor, int param);
int				check_cycles(t_env *env, int j);
void			exec_op(t_env *env, int j);
void			op_live(t_env *env, int j);
void			op_sti(t_env *env, int j);
void			op_ld(t_env *env, int j);
void			op_st(t_env *env ,int j);
void			op_add(t_env *env ,int j);
void			op_sub(t_env *env ,int j);
void			op_and(t_env *env ,int j);
void			op_or(t_env *env, int j);
void			op_xor(t_env *env, int j);
void			op_fork(t_env *env, int j);
void			op_zjmp(t_env *env, int j);
void			op_ldi(t_env *env ,int j);
void			op_lldi(t_env *env ,int j);
void			op_lld(t_env *env, int j);
void			op_lfork(t_env *env, int j);
void			op_aff(t_env *env, int j);

int				del_process(t_env *env);

// DEBUG
void	ft_print_memory(t_env *env);

#endif
