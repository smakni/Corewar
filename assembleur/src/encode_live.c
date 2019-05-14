#include "../../includes/asm.h"

static int		clean_quit(void **params, const int ret)
{
	ft_tabdel(params, ft_arrlen(params));
	return (ret);
}

int     ft_encode_live(t_parser *data)
{
    int     i;
    char    **params;

	data->bytecode[139] += 5;
    data->bytecode[data->index] = 1;
    data->index++;
    i = ft_strspn(data->line, " \t") + 4;
    i += ft_strspn(&data->line[i], " \t");
    if (!(params = ft_strsplit(&data->line[i], ',')))
	    return (FAIL);
    if (ft_arrlen((void*)params) != 1)
	    return (clean_quit((void*)params, FAIL));
    if (!(ft_encode_param(params[0], T_DIR, data, 0)))
        return (clean_quit((void*)params, FAIL));
    return (clean_quit((void*)params, SUCCESS));
}
