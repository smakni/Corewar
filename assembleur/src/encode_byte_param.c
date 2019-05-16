#include "../../includes/asm.h"

int		ft_encode_byte_param(const char *param)
{
	char	*trimmed;
	int		i;

	i = ft_strspn(param, " \t");
	if (param[i] == 'r')
		return (REG_CODE);
	if (param[i] == '%')
		return (DIR_CODE);
	if (!(trimmed = ft_strtrim(param)))
		return (FAIL);
	i = 0;
	if (trimmed[i] == '-')
		i++;
	if (ft_str_is_numeric(&trimmed[i]) || trimmed[0] == ':')
		return (IND_CODE);
	return (FAIL);
}
