#include "minishell.h"

int		is_end(char c)
{
	return (c == '\0');
}

int		is_eq(char c1, char c2)
{
	return (c1 == c2);
}

int		matcher(char *s1, char *s2)
{
	if (!is_end(s1[0]) && is_eq(s2[0], '*'))
		return (matcher(s1 + 1, s2) || matcher(s1, s2 + 1));
	if (is_end(s1[0]) && is_eq(s2[0], '*'))
		return (matcher(s1, s2 + 1));
	if (is_eq(s1[0], s2[0]) && !is_end(s1[0]) && !is_end(s2[0]))
		return (matcher(s1 + 1, s2 + 1));
	return (is_eq(s1[0], s2[0]) && is_end(s1[0]) && is_end(s2[0]));
}

int		starts_with_dot(char *path)
{
	return (path && path[0] == '.');
}

char **array_join(char **arr, int start, int end)
{
	char **res;
	int size;

	//ERROR MANAGEMENT
	size = sizeof_array(arr) - (end - start); //SIZE COULD BE 0
	printf("size: %d\n", size);
	res = (char **)ft_calloc((size + 1), sizeof(char *));
	
	//CHECK MALLOC
	int arr_index;
	int res_index;

	arr_index = 0;
	res_index = 0;
	while (arr_index < start)
	{
		res[res_index] = ft_strdup(arr[arr_index]); //COPY
		res_index++;
		arr_index++;
	}
	while (arr_index <= end)
	{
		res[res_index] = ft_strjoin_free(res[res_index], arr[arr_index]); //ft_strjoin_sepf(res[res_index], " ", arr[arr_index]); //NEED TO REPLACE BY STRJOIN_SEP WITH FREE
		arr_index++;
	}
	res_index++;
	while (arr[arr_index] != NULL)
	{
		res[res_index] = ft_strdup(arr[arr_index]); //COPY?
		res_index++;
		arr_index++;
	}
	res[size] = NULL;
	free_array(arr);
	return (res);
}

void prt(char *data)
{
	if (data != NULL)
		printf("|%s|\n", data);
	else
		printf("<null>\n");
}

char **find_pattern(char *str)
{
	int quote;
	int dquote;
	int i;
	int j;
	int start_d;
	int start_q;


	i = 0;
	quote = 0;
	dquote = 0;
	start_q = 0;
	start_d = 0;
	char **arr = ft_split(str, " ");
	iter_array(arr, prt);
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == '\"' && !quote)
			{
				if (dquote && start_d != i)
				{
					arr = array_join(arr, start_d, i);
					i = start_d;
					dquote = 0;
					break ;
				}
				else
				{
					start_d = i;
					dquote = 1;
				}
			}
			else if (arr[i][j] == '\'' && !dquote)
			{
				if (quote && start_q != i)
				{
					arr = array_join(arr, start_q, i);
					i = start_q;
					quote = 0;
					break ;
				}
				else
				{
					start_q = i;
					quote = 1;
				}
			}
			j++;
		}
		i++;
	}
	//check if quote and dquote are not closed
	if (dquote || quote)
		printf("Quotes are not closed\n");	
	return (arr);
}

//Count slashes in pattern will give us directory diving depth

char *asterisk(char *pattern)
{ 
	DIR				*dir;
	char			*res;
	char			*sep;
    struct dirent	*entry;

	char *current;

	current = getcwd(NULL, 0);

    dir = opendir(current);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
	res = ft_strdup("");

    while ( (entry = readdir(dir)) != NULL)
	{
		if (matcher(entry->d_name, pattern) && !starts_with_dot(entry->d_name))
		{
			char *tmp;

			tmp = res;
			
			if (ft_strlen(res) != 0)
				sep = " ";
			else
				sep = "";
		
			res = ft_strjoin_sep(res, sep, entry->d_name);
			free(tmp);
		}
    };
    closedir(dir);
	return (res);
};

// int main(void)
// {
// 	char **res = find_pattern("\"Hello \'world \"my \'name is Ilnur\'");
// 	// char *pattern = "*";
// 	// asterisk(pattern);
	
// 	iter_array(res, prt);
// 	return (0);
// }