#include "../../includes/asm.h"

int		ft_memorize_label(const char *param, t_parser *data, int is_index)
{
	(void)param;
	(void)is_index;
	data->index += 2;
	return (SUCCESS);
}
