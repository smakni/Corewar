#include "../../includes/asm.h"

static int	clean_quit(char **param, const int ret)
{
	ft_strdel(param);
	return (ret);
}

static int	ft_encode_indirect(char *param, t_parser *data)
{
	data->bytecode[data->index] = 0;
	data->bytecode[data->index + 1] = ft_atoi(param);
	data->index += 2;
	return (clean_quit(&param, SUCCESS));
}

static int	ft_encode_direct(char *param, t_parser *data, int is_index)
{
	int	nb;

	if (ft_strlen(param) <= 1)
		return (clean_quit(&param, FAIL));
	if (param[1] == ':')
		ft_memorize_blank_label(param, data, is_index);
	else
	{
		if (ft_str_is_numeric(&param[1]) == false)
			return (clean_quit(&param, FAIL));
		if (is_index)
		{
			nb = (short)ft_atoi(&param[1]);
			data->bytecode[data->index] = nb >> 8;
			data->bytecode[data->index + 1] = nb;
			data->index += 2;
		}
		else
		{
			nb = ft_atoi(&param[1]);
			data->bytecode[data->index] = nb >> 24;
			data->bytecode[data->index + 1] = nb >> 16;
			data->bytecode[data->index + 2] = nb >> 8;
			data->bytecode[data->index + 3] = nb;
			data->index += 4;
		}		
	}
	return (clean_quit(&param, SUCCESS));
}

static int	ft_encode_register(char *param, t_parser *data)
{
	int	reg_nb;
	size_t len;

	len = ft_strlen(param);
	if (len <= 1 || len > 3)
		return (clean_quit(&param, FAIL));
	if (ft_str_is_numeric(&param[1]) == false)
		return (clean_quit(&param, FAIL));
	reg_nb = ft_atoi(&param[1]);
	if (reg_nb <= 0 || reg_nb > 16)
		return (clean_quit(&param, FAIL));
	data->bytecode[data->index] = reg_nb;
	data->index++;
	return (clean_quit(&param, SUCCESS));
}

int			ft_encode_param(const char *rough_param, const int type_param, t_parser *data, int is_index)
{
	char	*param;

	if (!(param = ft_strtrim(rough_param)))
		return (FAIL);
	if (T_REG & type_param)
		if (param[0] == 'r')
			return (ft_encode_register(param, data));
	if (T_DIR & type_param)
		if (param[0] == '%')
			return (ft_encode_direct(param, data, is_index));
	if (T_IND & type_param)
		if (ft_str_is_numeric(param))
			return (ft_encode_indirect(param, data));
	return (FAIL);
}
