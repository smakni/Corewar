#include "../../includes/asm.h"

int				ft_encode_zjmp(t_parser *data)
{
	int		i;

	data->bytecode[data->index] = 9;
	data->index++;
	i = ft_strspn(data->line, " \t") + 4;
	i += ft_strspn(&data->line[i], " \t");
	ft_printf("line = %s\n", &data->line[i]);
	if (!(ft_encode_param(&data->line[i], T_DIR, data, 1)))
		return (FAIL);
	return (SUCCESS);
}
