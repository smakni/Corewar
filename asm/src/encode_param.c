#include "../includes/asm.h"

char	bytecode[10];

static int	ft_encode_indirect(const char *param, int *index)
{
	bytecode[*index] = 0;
	bytecode[*index + 1] = ft_atoi(param);
	*index += 2;
	return (SUCCESS);
}

static int	ft_encode_direct(const char *param, int *index)
{
	if (ft_strlen(param) <= 1)
		return (FAIL);
	if (param[1] == ':')
		ft_memorize_label(param, index);
	else
	{
		if (ft_str_is_numeric(&param[1]) == false)
			return (FAIL);
		bytecode[*index] = 0;
		bytecode[*index + 1] = ft_atoi(&param[1]);
		*index += 2;
	}
	return (SUCCESS);
}

static int	ft_encode_register(const char *param, int *index)
{
	int	reg_nb;

	if (ft_strlen(param) <= 1)
		return (FAIL);
	if (ft_str_is_numeric(&param[1]) == false)
		return (FAIL);
	reg_nb = ft_atoi(&param[1]);
	if (reg_nb <= 0 || reg_nb > 16)
		return (FAIL);
	bytecode[*index] = reg_nb;
	(*index)++;
	return (SUCCESS);
}

int			ft_encode_param(const char *param, const int type_param, int *index)
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
	return (FAIL);
}
