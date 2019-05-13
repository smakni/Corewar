#include "../../includes/asm.h"

int		ft_encode_byte_param(const char *param)
{
	char	*trimmed;
	int		i;

	i = ft_strspn(param, " \t");
	if (param[i] == 'r')
		return (0b01);
	if (param[i] == '%')
		return (0b10);
	if (!(trimmed = ft_strtrim(param)))
		return (FAIL);
	if (ft_str_is_numeric(trimmed))
		return (0b11);
	return (FAIL);
}
