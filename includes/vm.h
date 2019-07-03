/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:10:12 by smakni            #+#    #+#             */
/*   Updated: 2019/07/03 15:49:15 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "op.h"
# include <curses.h>
# include <limits.h>

# define MAX_OP_LEN				11
# define MAX_SIZE	(CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
# define FAIL					0
# define SUCCESS				1
# define ARR_SIZE				1024
# define GO_BACK				1
# define DUMP					64
# define CHAMP_EXTENSION		".cor\0"

typedef struct		s_op_vars
{
	int	cursor;
	int	v1;
	int	v2;
	int	v3;
}					t_op_vars;

typedef	struct 		s_op
{
	unsigned		code;
	unsigned char	saved[MAX_OP_LEN];
	char			*param[MAX_ARGS_NUMBER];
	char 			*name;
}					t_op;

typedef	struct		s_player
{
	header_t		header;
	unsigned		id;
	int				last_live;
}					t_player;

typedef struct		s_process
{
	unsigned		id;
	unsigned 		r[REG_NUMBER + 1];
	t_op			op;
	int				pc;
	int				cycles;
	int				nb;
	int				color;
	int				dest;
	int				bold;
	int				live;
	int				nb_live;
	int				last_live;
	int				check_args;
	int				cycle_to_life;
	char			carry;
}					t_process;

typedef struct		s_env
{
	unsigned char	memory[MEM_SIZE];
	int				op_cycles[17];
	void			(*op_fun[16])(struct s_env *, unsigned int);
	t_player		player[MAX_PLAYERS];
	t_process		*process;
	unsigned		nb_process;
	unsigned		living_proc;
	unsigned		nb_player;
	unsigned		capacity;
	int				live_period;
	int				err_code;
	int				fd;
	int				dump;
	int				speed;
	int				cycle_to_die;
	int				cycle_index;
	int				option;
	int				goback;
	int				verb;
	int				aff;
	char			*err_msg;
	WINDOW			*around_memory;
	WINDOW			*mem;
	WINDOW			*around_infos;
	WINDOW			*infos;
	WINDOW			*around_verbos;
	WINDOW			*verbos;
	WINDOW			*state;
	WINDOW			*commands;
	WINDOW			*trace[GO_BACK];
	WINDOW			*traceinfos[GO_BACK];
	WINDOW			*traceverbos[GO_BACK];
}					t_env;

int					ft_parse_argc(int argc, char **argv, t_env *env);
int					write_champ(t_env *env);
int					read_memory(t_env *env);
int					ft_realloc_tab(t_env *env);
int					read_bytes(unsigned char *line, int index, int n);
int					safe_open(const char *pathname, t_env *data, const int flags);
int					type_param(unsigned char byte, int param);
int 				decode_byte_param(unsigned char param, int is_index, int len);
int					get_value(t_env *env, unsigned j, int *cursor, int param);
int					get_value_index(t_env *env, unsigned j, int *cursor, int param);
int					check_cycles(t_env *env, unsigned j);
int					check_args(t_env *env, unsigned int j, int cursor, int nb_param);
void				exec_op(t_env *env, unsigned j);
void				op_live(t_env *env, unsigned j);
void				op_sti(t_env *env, unsigned j);
void				op_ld(t_env *env, unsigned j);
void				op_st(t_env *env ,unsigned j);
void				op_add(t_env *env ,unsigned j);
void				op_sub(t_env *env ,unsigned j);
void				op_and(t_env *env ,unsigned j);
void				op_or(t_env *env, unsigned j);
void				op_xor(t_env *env, unsigned j);
void				op_fork(t_env *env, unsigned j);
void				op_zjmp(t_env *env, unsigned j);
void				op_ldi(t_env *env ,unsigned j);
void				op_lldi(t_env *env ,unsigned j);
void				op_lld(t_env *env, unsigned j);
void				op_lfork(t_env *env, unsigned j);
void				op_aff(t_env *env, unsigned j);
int					del_processess(t_env *env);
void				save_op(t_env *env, unsigned j);
void				save_reg_param(t_env *env, int j, int value, int index);
void				save_ind_param(t_env *env, int j, int value, int index);
void				save_dir_param(t_env *env, int j, int value, int index);

int					ft_sort_argc(t_env *env, t_player *tmp);
int					ft_check_args_validity(char **argv, t_env *env);

// DEBUG
void				ft_print_memory(t_env *env);
// void				save_param(t_env *env, int j, int value, int code, int index);
void				first_visu(t_env *env);
void				update_visu(t_env *env, int dest, unsigned j);
void				redraw_pc(t_env *env, int pc, int len);
void				print_infos(t_env *env);
//void				redraw_pc(t_env *env, int pc, int len);
void				key_events(t_env *env);
void				verbos(t_env *env, unsigned j, int save);
void				verbos_visu(t_env *env, unsigned j, int save);
void				remove_bold(t_env *env, unsigned j);
void				fill_commands_mv_back(t_env *env);
void				fill_commands(t_env *env);
void 				mv_back(t_env *env);
void				exit_clean(t_env *env);
void				protect_wclear(t_env *env, WINDOW *toclear);
void				protect_wrefresh(t_env *env, WINDOW *torefresh);
void				protect_werase(t_env *env, WINDOW *toerase);
void				print_pc(t_env *env, unsigned j, int save);
int					print_error(char *error);
void				init_color_palet(void);
void				fill_first(t_env *env);
void				write_champ_visu(t_env *env, unsigned j);
void				read_memory_visu(t_env *env);
int					check_last_live(t_env *env);
WINDOW				*protect_dupwin(t_env *env, WINDOW *to_dup);

#endif
