#include "../../includes/asm.h"

static int	clean_quit(char	**tmp, char **cor_file, t_parser *data,
				const int ret)
{
	if (*cor_file == NULL || cor_file == NULL)
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc.";
	}
	else
	{
		data->err_code = 6;
		data->err_msg = "Fail to create .cor file.";		
	}
	ft_strdel(tmp);
	ft_strdel(cor_file);
	return (ret);
}

int			ft_write_cor(t_parser *data, const char *path_name)
{
	char 	*cor_file;
	char	*tmp;
	size_t	len;
	
	tmp = ft_strrchr(path_name, '.');
	if (tmp == NULL)
		return (FAIL);
	len = tmp - path_name;
	if (!(cor_file = ft_strndup(path_name, len)))
		return (clean_quit(NULL, NULL, data, FAIL));
	tmp = cor_file;
	if (!(cor_file = ft_strjoin(cor_file, ".cor")))
		return (clean_quit(&tmp, NULL, data, FAIL));
	if (!(safe_open(cor_file, data, O_CREAT | O_TRUNC | O_WRONLY)))
		return (clean_quit(&tmp, &cor_file, data, FAIL));
	write(data->fd, data->bytecode, data->index);
	ft_printf("Writing output program to %s\n", cor_file);
	close (data->fd);
	ft_strdel(&tmp);
	ft_strdel(&cor_file);
	return (SUCCESS);	
}
