#include "../../includes/asm.h"

int		ft_parse_args(t_parser *data, char **params)
{
	int		i;
	char	byte;
	int		tmp;

	i = 0;
	byte = 0;
	while (params[i])
	{
		if (!(tmp = ft_encode_byte_param(params[i])))
			return (FAIL);
		byte += tmp;
		byte <<= 2;
		i++;
	}
	data->bytecode[data->index] = byte;
	data->index++;
	return (SUCCESS);
}
