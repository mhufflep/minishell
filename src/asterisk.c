#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

int		matcher(char *s1, char *s2)
{
	if (s1[0] != '\0' && s2[0] == '*')
		return (matcher(s1 + 1, s2) || matcher(s1, s2 + 1));
	if (s1[0] == '\0' && s2[0] == '*')
		return (matcher(s1, s2 + 1));
	if (s1[0] == s2[0] && s1[0] != '\0' && s2[0] != '\0')
		return (matcher(s1 + 1, s2 + 1));
	return (s1[0] == s2[0] && s1[0] == '\0' && s2[0] == '\0');
}

int		starts_with_dot(char *path)
{
	return (path[0] == '.');
}

char *join_path(char *s1, char *s2, char *sep)
{
	int		len_first;
	int		len_second;
	int		len_sep;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len_first = ft_strlen(s1);
	len_second = ft_strlen(s2);
	len_sep = ft_strlen(sep);
	res = (char *)malloc(len_first + len_sep + len_second + 1);
	if (!res)
		return (NULL);
	ft_memmove(res, s1, len_first);
	ft_memmove(&res[len_first], sep, len_sep);
	ft_memmove(&res[len_first + len_sep], s2, len_second);
	res[len_first + len_second + len_sep] = '\0';
	
	return (res);
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

    dir = opendir("../");
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
		
			res = join_path(res, entry->d_name, sep);
			free(tmp);
		}
    };
	printf("%s\n", res);

    closedir(dir);
};

int main(void)
{
	char *pattern = "*";
	asterisk(pattern);
	return (0);
}