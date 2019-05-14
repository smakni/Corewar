#include "../../includes/asm.h"

// static int 	print_list(t_bytes *list)
// {
// 	ft_printf("addr list => %p\n", list);
// 	while (list)
// 	{
// 		ft_printf("Label -> %s | %i | %i\n", list->label, list->index, list->size);
// 		list = list->next;
// 	}
// 	return (SUCCESS);
// }

int		ft_memorize_blank_label(const char *param, t_parser *data, int is_index)
{
	t_bytes	*elem;

	if (!(elem = bytes_init(data)))
		return (FAIL);
	if (!(elem->label = ft_strdup(&param[2])))
	{
		data->err_code = 2;
		data->err_msg = "Fail to malloc";
		return (FAIL);
	}
	elem->index = data->index;
	elem->index_instruction = data->index_instruction;
	if (is_index)
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
