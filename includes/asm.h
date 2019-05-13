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

typedef struct	s_data
{
	char			*line;
	struct s_data	*next;
}				t_data;

typedef struct	s_parser
{
	char	bytecode[CHAMP_MAX_SIZE + 1];
	char	*line;
	char	*err_msg;
	int		err_code;
	int		fd;
	int		index;

}				t_parser;

int				ft_strccmp(const char *s1, const char *s2, const char limit);
int				ft_memorize_label(const char *param, t_parser *data);
t_parser		*parser_init(void);
int				ft_write_cor(t_parser *data, const char *path_name);
int				safe_open(const char *pathname, t_parser *data, const int flags);

/*	ENCODING FUNCTIONS	*/

int				ft_encode_cmd(const char *str, int *index);
int				ft_encode_param(const char *rough_param, const int type_param, t_parser *data);
int				ft_encode_sti(t_parser *data);

#endif
