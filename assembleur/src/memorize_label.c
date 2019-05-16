#include "../../includes/asm.h"

int		ft_memorize_blank_label(const char *param, t_parser *data, int is_index)
{
	t_bytes	*elem;
	int 	i;

	if (!(elem = bytes_init(data)))
		return (FAIL);
	i = ft_strlen_c(param, ':') + 1;
	if (!(elem->label = ft_strdup(&param[i])))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc";
		return (FAIL);
	}
	elem->index = data->index;
	elem->index_instruction = data->index_instruction;
	if (is_index || param[0] == ':')
	{
		elem->size = 2;
		data->index += 2;
	}
	else
	{
		elem->size = 4;
		data->index += 4;
	}
	ft_add_byte_elem(&data->blanks, elem);
	return (SUCCESS);
}
