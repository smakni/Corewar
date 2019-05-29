#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define SIZE_BUFFER	4096
# define IDENTICAL	0
# define SUCCESS	1
# define FAIL		0

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
	t_bytes			*blanks;
	t_bytes			*labels;
	unsigned char	*bytecode;
	char			*pathname;
	char			*line;
	int				nb_line;
	char			*err_msg;
	int				err_code;
	int				fd;
	unsigned int	index;
	unsigned int	nb_realloc;
	int				index_instruction;
	int				comment_flag;
	int				eol;
	char			header_name_flag;
	char			header_comment_flag;
	char			syntax_flag;
}				t_parser;

int				ft_strccmp(const char *s1, const char *s2);
int				ft_memorize_blank_label(const char *param, t_parser *data, int is_index);
int				ft_write_cor(t_parser *data, const char *path_name);
void			write_prog_size(t_parser *data);
int				safe_open(const char *pathname, t_parser *data, const int flags);

void			ft_add_byte_elem(t_bytes **list, t_bytes *elem);
void			ft_del_byte_elem(t_bytes **list, t_bytes *elem);

int				line_parser(t_parser *data, int i, int label_flag);
int				reader(t_parser *data);
int				ft_format_line(t_parser *data, int i);

/*	MEMORY FUNCTIONS	*/

t_parser		*parser_init(char *av);
t_bytes			*bytes_init(t_parser *data);
void			ft_bytesdel(t_bytes **list);
int				ft_realloc_bytecode(t_parser *data);
int				ft_format_line(t_parser *data, int i);

/*	ENCODING FUNCTIONS	*/

int				save_label_address(t_parser *data);
int				check_label_chars(char *str);
void			ft_fill_addr(t_parser *data);
int				ft_parse_args(t_parser *data, char **params);
int				ft_encode_register(char *param, t_parser *data);
int				ft_encode_direct(char *param, t_parser *data, int is_index);
int				ft_encode_indirect(char *param, t_parser *data);
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
int				encode_comment(t_parser *data, int i);
int				encode_multi_comment(t_parser *data);
int				encode_name(t_parser *data, int i);
int				encode_multi_name(t_parser *data);
int				ft_strlen_c(const char *str, char c);

#endif
