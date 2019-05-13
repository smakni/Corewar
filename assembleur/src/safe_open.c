#include "../../includes/asm.h"

int		safe_open(const char *pathname, t_parser *data, const int flags)
{
	int		fd;

	fd = open(pathname, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		data->err_code = 1;
		data->err_msg = "Open() failed: Please, check permissions or pathname.";
		return (FAIL);
	}
	data->fd = fd;
	return (SUCCESS);
}
