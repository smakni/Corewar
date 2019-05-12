#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define IDENTICAL	0
<<<<<<< HEAD

int		ft_strccmp(const char *s1, const char *s2, const char limit);
int		ft_encode_sti(const char *str, int *index);
=======
# define SUCCESS	1
# define FAIL		0
>>>>>>> origin/jg

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

typedef struct	s_rex
{
	char	**str;
	char	bytecode[CHAMP_MAX_SIZE + 1];
	int		index;
	int		error;
}				t_rex;


int				ft_strccmp(const char *s1, const char *s2, const char limit);
int				ft_encode_cmd(const char *str, int *index);
int				ft_encode_param(const char *param, const int type_param, int *index);
int				ft_memorize_label(const char *param, int *index);
t_rex			*rex_init(char **str);

#endif
