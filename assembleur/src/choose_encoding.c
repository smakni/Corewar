#include"../../includes/asm.h"

static int 		ft_strlen_c(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int		ft_format_line(t_parser *data, int i)
{
	char *tmp;

	tmp = NULL;
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
	ft_strdel(&data->line);
	data->line = tmp;
	data->index_instruction = data->index;
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
