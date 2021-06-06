#include "minishell.h"

int		is_dir(char *directory)
{
	DIR	*dir;

	dir = opendir(directory);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
    }
	return (0);
}

int		is_in_dir(char *name, char *directory)
{ 
	DIR				*dir;
    struct dirent	*entry;
	int found;

	dir = opendir(directory);	
	if (!dir)
	{
		return (0);
	}

	found = 0;
    while (!found)
	{
		entry = readdir(dir);

		if (entry == NULL)
			break ;
		if (!ft_strcmp(entry->d_name, ".") ||
			!ft_strcmp(entry->d_name, ".."))
			continue;
		if (!ft_strcmp(entry->d_name, name))
			found = 1;
	}

	closedir(dir);
	return (found);
};