#include"../../includes/asm.h"

static int	clean_quit(char **tmp, const int ret)
{
	ft_strdel(tmp);
	return (ret);
}

static char *insert_space(t_parser *data, char *tmp)
{
	char	*tmp2;
	int 	j;

	j = 0;
	tmp2 = NULL;
	while (tmp[j] && tmp[j] != ' ' && tmp[j] != '\t' 
				&& tmp[j] != '%' && tmp[j] != ':')
		j++;
	if (tmp[j] == '%' || tmp[j] == ':')
	{
		j = 0;
		if (!(tmp2 = ft_memalloc(sizeof(char) * ((ft_strlen(tmp) + 2)))))
		{
			data->err_code = 2;
			data->err_msg = "Fail to malloc a char*";
			return (NULL);
		}
		while (tmp[j] != '%' && tmp[j] != ':')
		{
			tmp2[j] = tmp[j];
			j++;
		}
		tmp2[j++] = ' ';
		while (tmp[j - 1])
		{
			tmp2[j] = tmp[j - 1];
			j++;
		}
	}
	return (tmp2);
}

static int		ft_format_line(t_parser *data, int i)
{
	char *tmp;
	char *tmp2;

	data->index_instruction = data->index;
	ft_printf("line = %s\n", &data->line[i]);
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
	ft_printf("format_line = %s\n", data->line);
	if (tmp2)
		ft_strdel(&tmp);
	return (SUCCESS);
}

static int		choose_encoding_suite(t_parser *data)
{
	if (ft_strccmp("lld", data->line) == IDENTICAL)
		return (ft_encode_lld(data));
	if (ft_strccmp("lldi", data->line) == IDENTICAL)
		return (ft_encode_lldi(data));
	if (ft_strccmp("lfork", data->line) == IDENTICAL)
		return (ft_encode_lfork(data));
	if (ft_strccmp("aff", data->line) == IDENTICAL)
		return (ft_encode_aff(data));
	return (FAIL);
}

int		choose_encoding(t_parser *data, int i)
{
	ft_format_line(data, i);
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
	if (ft_strccmp("fork", data->line) == IDENTICAL)
		return (ft_encode_fork(data));
	return (choose_encoding_suite(data));
}
