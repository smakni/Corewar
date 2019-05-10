#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	void	*txt;

	txt = (void*)0x0b68;
	fd = open("test.cor", O_WRONLY);
	if (fd)
		write(1, "ici", 3);
	else
		write (1, "la", 2);
	write(fd, "\13h\1",3);
	close(fd);
	return (0);
}
