#include "../../includes/asm.h"

int		ft_memorize_label(const char *param, t_parser *data)
{
	(void)param;
	data->index += 2;
	return (SUCCESS);
}
