#include "../includes/asm.h"

int		ft_encode_cmd(const char *str, int *index)
{
	if (ft_strccmp("sti", str, ' ') == IDENTICAL)
		return (ft_encode_sti(str, index));
	return (FAIL);
}
