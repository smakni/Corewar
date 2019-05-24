#include"../../includes/asm.h"

static int	clean_quit(char **tmp, const int ret)
{
	ft_strdel(tmp);
	return (ret);
}

static char *insert_space(t_parser *data, char *tmp)
{
	char	*tmp2;
	char	*tmp3;
	int 	j;

	j = 0;
	tmp2 = NULL;
	while (tmp[j] && tmp[j + 1])
	{
		if (tmp[j] == ' ' || tmp[j] == '\t' || tmp[j] == '%' 
			|| tmp[j] == ':' || ft_isdigit(tmp[j]) || tmp[j] == '-')
			break ;
		if (tmp[j] == 'r' && ft_isdigit(tmp[j + 1]))
		{
			data->err_code = 3;
			data->err_msg = "Syntax error near line ";
			return (NULL);
		}
		j++;
	}
	if (tmp[j] == '\0' || tmp[j] == ' ' || tmp[j] == '\t')
		return (tmp2);
	if (!(tmp2 = ft_memjoin((void *)tmp, j, (void *)" ", 1)))
		return (NULL);
	tmp3 = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, &tmp[j])))
	{
		ft_strdel(&tmp3);
		return (NULL);
	}
	ft_strdel(&tmp3);
	return (tmp2);
}

static int		ft_format_line(t_parser *data, int i)
{
	char *tmp;
	char *tmp2;

	data->index_instruction = data->index;
	if (ft_strrchr(data->line, '#'))
	{
		if (!(tmp = ft_strsub(data->line, i, ft_strlen_c(&data->line[i], '#'))))
			return (FAIL);
	}
	else if (ft_strrchr(data->line, ';'))
	{
		if (!(tmp = ft_strsub(data->line, i, ft_strlen_c(&data->line[i], ';'))))
			return (FAIL);
	}
	else
		if (!(tmp = ft_strdup(&data->line[i])))
			return (FAIL);
	tmp2 = insert_space(data, tmp);
	if (data->err_code != 0)
		return (clean_quit(&tmp, FAIL));
	ft_strdel(&data->line);
	data->line = (tmp2 == NULL) ? tmp : tmp2;
	if (tmp2)
		ft_strdel(&tmp);
	return (SUCCESS);
}

static int		choose_encoding_suite(t_parser *data)
{
	if (ft_strccmp("fork", data->line) == IDENTICAL)
		return (ft_encode_fork(data));
	if (ft_strccmp("lld", data->line) == IDENTICAL)
		return (ft_encode_lld(data));
	if (ft_strccmp("lldi", data->line) == IDENTICAL)
		return (ft_encode_lldi(data));
	if (ft_strccmp("lfork", data->line) == IDENTICAL)
		return (ft_encode_lfork(data));
	if (ft_strccmp("aff", data->line) == IDENTICAL)
		return (ft_encode_aff(data));
	data->err_code = 7;
	data->err_msg = "Invalid instruction near line ";
	return (FAIL);
}

int		choose_encoding(t_parser *data, int i)
{
	data->syntax_flag = 1;
	if (!(ft_format_line(data, i)))
		return (FAIL);
	if (ft_strccmp("live", data->line) == IDENTICAL)
		return (ft_encode_live(data));
	if (ft_strccmp("ld", data->line) == IDENTICAL)
		return (ft_encode_ld(data));
	if (ft_strccmp("st", data->line) == IDENTICAL)
		return (ft_encode_st(data));
	if (ft_strccmp("add", data->line) == IDENTICAL)
		return (ft_encode_add(data));
	if (ft_strccmp("sub", data->line) == IDENTICAL)
		return (ft_encode_sub(data));
	if (ft_strccmp("and", data->line) == IDENTICAL)
		return (ft_encode_and(data));
	if (ft_strccmp("or", data->line) == IDENTICAL)
		return (ft_encode_or(data));
	if (ft_strccmp("xor", data->line) == IDENTICAL)
		return (ft_encode_xor(data));
	if (ft_strccmp("zjmp", data->line) == IDENTICAL)
		return (ft_encode_zjmp(data));
	if (ft_strccmp("ldi", data->line) == IDENTICAL)
		return (ft_encode_ldi(data));
	if (ft_strccmp("sti", data->line) == IDENTICAL)
		return (ft_encode_sti(data));
	return (choose_encoding_suite(data));
}
