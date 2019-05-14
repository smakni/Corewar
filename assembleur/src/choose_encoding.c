#include"../../includes/asm.h"

int		choose_encoding(t_parser *data, int i)
{
	if (ft_strccmp("live", &data->line[i]) == IDENTICAL)
		return (ft_encode_live(data));
	if (ft_strccmp("ld", &data->line[i]) == IDENTICAL)
		return (ft_encode_ld(data));
	if (ft_strccmp("st", &data->line[i]) == IDENTICAL)
		return (ft_encode_st(data));
	if (ft_strccmp("add", &data->line[i]) == IDENTICAL)
		return (ft_encode_add(data));
	if (ft_strccmp("sub", &data->line[i]) == IDENTICAL)
		return (ft_encode_sub(data));
	if (ft_strccmp("and", &data->line[i]) == IDENTICAL)
		return (ft_encode_and(data));
	if (ft_strccmp("or", &data->line[i]) == IDENTICAL)
		return (ft_encode_or(data));
	if (ft_strccmp("xor", &data->line[i]) == IDENTICAL)
		return (ft_encode_xor(data));
	if (ft_strccmp("zjmp", &data->line[i]) == IDENTICAL)
		return (ft_encode_zjmp(data));
	if (ft_strccmp("ldi", &data->line[i]) == IDENTICAL)
		return (ft_encode_ldi(data));
	if (ft_strccmp("sti", &data->line[i]) == IDENTICAL)
		return (ft_encode_sti(data));
	if (ft_strccmp("fork", &data->line[i]) == IDENTICAL)
		return (ft_encode_fork(data));
	return (choose_encoding_suite(data, i));
}

int		choose_encoding_suite(t_parser *data, int i)
{
	if (ft_strccmp("lld", &data->line[i]) == IDENTICAL)
		return (ft_encode_lld(data));
	if (ft_strccmp("lldi", &data->line[i]) == IDENTICAL)
		return (ft_encode_lldi(data));
	if (ft_strccmp("lfork", &data->line[i]) == IDENTICAL)
		return (ft_encode_lfork(data));
	if (ft_strccmp("aff", &data->line[i]) == IDENTICAL)
		return (ft_encode_aff(data));
	return (0);
}
