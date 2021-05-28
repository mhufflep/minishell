#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

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

// int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result)
// {

// }

// char *asterisk2(char *dir, char *pattern, char *res)
// { 
// 	DIR				*dir;
// 	char			*res;
// 	char			*sep;
//     struct dirent	*entry;


// 	char *current;

// 	current = getcwd(NULL, 0);

//     dir = opendir(dir);
//     if (!dir)
// 		return ;
	
// 	// res = ft_strdup("");

//     while ( (entry = readdir(dir)) != NULL)
// 	{
// 		if (opendir(entry->d_name))
// 		if (matcher(entry->d_name, pattern) && !starts_with_dot(entry->d_name))
// 		{
			
// 			char *tmp;

// 			tmp = res;
// 			if (ft_strlen(res) != 0)
// 				sep = " ";
// 			else
// 				sep = "";
		
// 			res = join_path(res, entry->d_name, sep);
// 			free(tmp);
// 		}
//     };
// 	printf("%s\n", res);

//     closedir(dir);
// };


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
// 	char *pattern = "*";
// 	asterisk(pattern);
// 	return (0);
// }