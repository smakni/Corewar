#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

# define IDENTICAL	0

int		ft_strccmp(const char *s1, const char *s2, const char limit);

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

#endif
