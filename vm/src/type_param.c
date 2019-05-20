#include "../../includes/vm.h"

int	type_param(unsigned char byte, int param)
{
    char    mask;
    char    tmp;

    mask = 0b00000011;
    tmp = mask & (byte >> ((3 - param + 1) * 2));
    return (tmp);
}
