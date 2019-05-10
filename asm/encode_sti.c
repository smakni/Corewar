#include "../includes/asm.h"

char	bytecode[10];

int		ft_save_label(const char *param, int *index)
{
	(void)param;
	*index += 2;
	return (1);
}

int		ft_encode_register(const char *param, int *index)
{
	if (ft_strlen(param) <= 1)
		return (0);
	bytecode[*index] = ft_atoi(&param[1]);
	(*index)++;
	return (1);
}

int		ft_encode_direct(const char *param, int *index)
{
	if (ft_strlen(param) <= 1)
		return (0);
	if (param[1] == ':')
		ft_save_label(param, index);
	else
	{
		bytecode[*index] = 0;
		bytecode[*index + 1] = ft_atoi(&param[1]);
		*index += 2;
	}
	return (1);
}

int		ft_encode_indirect(const char *param, int *index)
{
	bytecode[*index] = 0;
	bytecode[*index + 1] = ft_atoi(param);
	*index += 2;
	return (1);
}

int		ft_encode_param(const char *param, const int type_param, int *index)
{
	if (T_REG & type_param)
		if (param[0] == 'r')
			return (ft_encode_register(param, index));
	if (T_DIR & type_param)
		if (param[0] == '%')
			return (ft_encode_direct(param, index));
	if (T_IND & type_param)
		if (ft_str_is_numeric(param))
			return (ft_encode_indirect(param, index));
	return (0);
}

int		ft_encode_sti(const char *str, int *index)
{
	int		i;
	char	**params;

	bytecode[*index] = 11;
	(*index)++;
	i = 3;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!(params = ft_strsplit(&str[i], ',')))
		return (0);
	if (ft_arrlen((void*)params) != 3)
		return (0);
	if (!(ft_encode_param(params[0], T_REG, index)))
		return (0);
	if (!(ft_encode_param(params[1], T_REG | T_DIR | T_IND, index)))
		return (0);
	if (!(ft_encode_param(params[2], T_REG | T_DIR, index)))
		return (0);
	return (1);
}

int		ft_encode_cmd(const char *str, int *index)
{
	if (ft_strccmp("sti", str, ' ') == IDENTICAL)
		return (ft_encode_sti(str, index));
	return (0);
}

int	main(void)
{
	int	index;

	index = 0;
	if (!(ft_encode_cmd("sti r1,13,%1", &index)))
		ft_printf("ERROR\n");
	else
		write(1, bytecode, index);
	return (0);
}
