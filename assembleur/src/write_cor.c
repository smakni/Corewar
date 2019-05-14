#include "../../includes/asm.h"

int	ft_write_cor(t_parser *data, const char *path_name)
{
	char 	*cor_file;
	char	*tmp;
	size_t	len;

	len = ft_strrchr(path_name, '.') - path_name;
	if (!(cor_file = ft_strndup(path_name, len)))
		return (FAIL);
	tmp = cor_file;
	if (!(cor_file = ft_strjoin(cor_file, ".cor")))
		return (FAIL);
	if (!(safe_open(cor_file, data, O_CREAT | O_TRUNC | O_WRONLY)))
		return (FAIL);
	write(data->fd, data->bytecode, data->index);
	ft_printf("Writing output program to %s\n", cor_file);
	close (data->fd);
	ft_strdel(&tmp);
	ft_strdel(&cor_file);
	return (SUCCESS);	
}