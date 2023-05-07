#include "./utils.h"

void	free_double(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	free_tokens(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens && tokens[i])
	{
		j = 0;
		while (tokens[i][j])
			free(tokens[i][j++]);
		free(tokens[i++]);
	}
	if (tokens)
		free(tokens);
}

void	free_lst(t_command_list *lst)
{
	t_command_list	*ptr;

	while (lst)
	{
		ptr = lst->next;
		if (lst->path)
			free(lst->path);
		if (lst->param)
			free_double(lst->param);
		if (lst->command)
			free(lst->command);
		free(lst);
		lst = ptr;
	}
	if (lst)
		free(lst);
}
