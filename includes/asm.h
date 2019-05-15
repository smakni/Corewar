#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define IDENTICAL	0
# define SUCCESS	1
# define FAIL		0

typedef struct	s_op
{
	char		*cmd;
	int			nb_arg;
	int			*arg_type;
	int			code_cmd;
	int			cycles;
	char		*msg;
	int			oct_code;
	int			dontknowwhat;
}				t_op;

typedef struct	s_bytes
{
	char			*label;
	int				index;
	int				size;
	int				index_instruction;
	struct s_bytes	*next;
}				t_bytes;

typedef struct	s_parser
{
	t_bytes	*blanks;
	t_bytes	*labels;
	char	bytecode[CHAMP_MAX_SIZE + 100000000 + 1];
	char	*line;
	char	*err_msg;
	int		err_code;
	int		fd;
	int		index;
	int		index_instruction;
	int		comment_flag;
}				t_parser;

int				ft_strccmp(const char *s1, const char *s2);
int				ft_memorize_blank_label(const char *param, t_parser *data, int is_index);
t_parser		*parser_init(void);
t_bytes			*bytes_init(t_parser *data);
int				ft_write_cor(t_parser *data, const char *path_name);
int				safe_open(const char *pathname, t_parser *data, const int flags);

void	ft_add_byte_elem(t_bytes **list, t_bytes *elem);
void	ft_del_byte_elem(t_bytes **list, t_bytes *elem);

/*	ENCODING FUNCTIONS	*/

void			ft_fill_addr(t_parser *data);
int				ft_parse_args(t_parser *data, char **params);
int				ft_encode_byte_param(const char *param);
int				ft_encode_param(const char *rough_param, const int type_param, t_parser *data, int is_index);
int				choose_encoding(t_parser *data, int i);
int				ft_encode_sti(t_parser *data);
int				ft_encode_and(t_parser *data);
int				ft_encode_sub(t_parser *data);
int				ft_encode_or(t_parser *data);
int				ft_encode_xor(t_parser *data);
int				ft_encode_zjmp(t_parser *data);
int				ft_encode_ldi(t_parser *data);
int				ft_encode_fork(t_parser *data);
int				ft_encode_lfork(t_parser *data);
int				ft_encode_live(t_parser *data);
int				ft_encode_ld(t_parser *data);
int				ft_encode_lld(t_parser *data);
int				ft_encode_lldi(t_parser *data);
int				ft_encode_st(t_parser *data);
int				ft_encode_add(t_parser *data);
int				ft_encode_aff(t_parser *data);
int				encode_header(t_parser *data, int i);
int				ft_strlen_c(const char *str, char c);

#endif
