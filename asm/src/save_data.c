#include "../includes/asm.h"

void	save_data(t_data **data, char *line)
{
	t_data *tmp;
	t_data *new;

	if (!(new = ft_memalloc(sizeof(t_data))))
		return ;
	new->line = line;
	new->next = NULL;
	if (*data == NULL)
	{
		*data = new;
		return ;
	}
	tmp = *data;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_free(t_data *data)
{
	t_data *tmp;

	while (data->next)
	{
		ft_printf("%s\n\n", data->line);
		tmp = data->next;
		free(data->line);
		free(data);
		data = tmp;
	}
	ft_printf("%s\n\n", data->line);
	free(data->line);
	free(data);
}
