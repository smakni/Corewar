#include "../../includes/asm.h"

int				ft_encode_fork(t_parser *data)
{
	int		i;

	data->bytecode[data->index] = 12;
	data->index++;
	i = ft_strspn(data->line, " \t") + 4;
	i += ft_strspn(&data->line[i], " \t");
	if (ft_strchr(&data->line[i], ','))
		return (FAIL);
	if (!(ft_encode_param(&data->line[i], T_DIR, data, 1)))
		return (FAIL);
	return (SUCCESS);
}