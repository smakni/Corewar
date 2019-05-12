#include "../includes/asm.h"

int		clean_quit(void **params, const int ret)
{
	ft_tabdel(params, ft_arrlen(params));
	return (ret);
}

int		ft_encode_sti(char bytecode[683], const char *str, int *index)
{
	int		i;
	char	**params;

	bytecode[*index] = 11;
	(*index)++;
	i = 3;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!(params = ft_strsplit(&str[i], ',')))
		return (FAIL);
	if (ft_arrlen((void*)params) != 3)
		return (clean_quit((void*)params, FAIL));
	if (!(ft_encode_param(params[0], T_REG, index)))
		return (clean_quit((void*)params, FAIL));
	if (!(ft_encode_param(params[1], T_REG | T_DIR | T_IND, index)))
		return (clean_quit((void*)params, FAIL));
	if (!(ft_encode_param(params[2], T_REG | T_DIR, index)))
		return (clean_quit((void*)params, FAIL));
	return (clean_quit((void*)params, SUCCESS));
}
