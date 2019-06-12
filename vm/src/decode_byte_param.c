#include "../../includes/vm.h"

int 	decode_byte_param(unsigned char param, int is_index, int len)
{
	int		op_len;
	char	mask;
	int		i;
	char	tmp;

	op_len = 1;
	i = 1;
	mask = 0b00000011;
	while (i <= len)
	{
		tmp = mask & param >> (8 - i * 2);
		if (tmp == 1)
			op_len++;
		else if (tmp == 2)
		{
			if (is_index)
				op_len += 2;
			else
				op_len += 4;
		}
		else if (tmp == 3)
			op_len += 2;
		i++;
	}
	//ft_printf("ADV --> %i\n", op_len);
	return (op_len);
}
