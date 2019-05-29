/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:10:12 by smakni            #+#    #+#             */
/*   Updated: 2019/05/29 14:13:04 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../ressources/op.h"
# include <curses.h>

# define MAX_CHAMP_CODE_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define FAIL		0
# define SUCCESS	1
# define ARR_SIZE	1024

typedef struct	s_champ
{
	header_t	header;
	unsigned	player_nb;
	int			pc;
	unsigned 	r[REG_NUMBER + 1];
	unsigned	last_live;
	int			nb_live;
	int			cycles;
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
	unsigned			nb_champs;
	unsigned			save_nb_champs;
	unsigned			nb_realloc;
	int					cycle_to_die;
	unsigned			cycle_index;
	int					visu;
	WINDOW				*around_memory;
	WINDOW				*mem;
	WINDOW				*around_infos;
	WINDOW				*infos;
}				t_env;

int				ft_parse_argc(int argc, char **argv, t_env *env);
int				write_champ(t_env *env);
int				read_memory(t_env *env);
int				read_multi_bytes(unsigned char *line, int index, int nb_bytes);
int				read_bytes(t_env *env, int index);
int				safe_open(const char *pathname, t_env *data, const int flags);
int				type_param(unsigned char byte, int param);
int 			decode_byte_param(unsigned char param, int is_index);
int				get_value(t_env *env, unsigned j, int *cursor, int param);
int				get_value_index(t_env *env, unsigned j, int *cursor, int param);
int				check_cycles(t_env *env, unsigned j);
void			exec_op(t_env *env, unsigned j);
void			op_live(t_env *env, unsigned j);
void			op_sti(t_env *env, unsigned j);
void			op_ld(t_env *env, unsigned j);
void			op_st(t_env *env ,unsigned j);
void			op_add(t_env *env ,unsigned j);
void			op_sub(t_env *env ,unsigned j);
void			op_and(t_env *env ,unsigned j);
void			op_or(t_env *env, unsigned j);
void			op_xor(t_env *env, unsigned j);
void			op_fork(t_env *env, unsigned j);
void			op_zjmp(t_env *env, unsigned j);
void			op_ldi(t_env *env ,unsigned j);
void			op_lldi(t_env *env ,unsigned j);
void			op_lld(t_env *env, unsigned j);
void			op_lfork(t_env *env, unsigned j);
void			op_aff(t_env *env, unsigned j);
void			aff_memory(t_env *env, unsigned j, int len);

int				del_process(t_env *env);

// DEBUG
void	ft_print_memory(t_env *env);
void	first_visu(t_env *env);
void	update_visu(t_env *env, unsigned j);
void	print_infos(t_env *env);

#endif
