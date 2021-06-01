#include "minishell.h"

int		is_dir(char *directory)
{
	DIR	*dir;

	dir = opendir(directory);	
	if (dir)
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

	dir = opendir(directory);	
	if (!dir)
	{
		return (0);
	};

    while (1)
	{
		entry = readdir(dir);

		if (entry == NULL)
			break ;
		if (!ft_strcmp(entry->d_name, ".") ||
			!ft_strcmp(entry->d_name, ".."))
			continue;
		if (!ft_strcmp(entry->d_name, name))
			return (1);
	};

	closedir(dir);
	return (0);
};