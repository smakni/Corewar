#include "../../includes/asm.h"

int				ft_encode_lfork(t_parser *data)
{
	int		i;

	data->bytecode[139] += 3;
	data->bytecode[data->index] = 15;
	data->index++;
	i = ft_strspn(data->line, " \t") + 5;
	i += ft_strspn(&data->line[i], " \t");
	if (ft_strchr(&data->line[i], ','))
		return (FAIL);
	if (!(ft_encode_param(&data->line[i], T_DIR, data, 1)))
		return (FAIL);
	return (SUCCESS);
}
