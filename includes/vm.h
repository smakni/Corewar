#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../ressources/op.h"

typedef struct	s_champ
{
	char		*name;
	int			player_nb;
}				t_champ;

typedef struct	s_env
{
	int					dump;
	int					nb_champs;
	t_champ				champ[4];
	unsigned char		memory[4096];
}				t_env;

void			ft_parse_argc(int argc, char **argv, t_env *env);
void			write_champ(t_env *env, char *argv);

#endif
