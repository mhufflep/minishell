#include "minishell.h"

void	print_export_node(void *content)
{
	char **arr;

	if (content != NULL)
	{
		arr = key_val_split((char *)content, '=');
		printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		free_array(arr);
	}
}

char	**key_val_split(char *str, char sep)
{
	char **arr;
	int i;

	i = 0;
	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		throw_error("Bad alloc");
	ft_memset(arr, 0, sizeof(char *) * 2);
	while (str && str[i] != '\0')
	{
		if (str[i] == '=')
		{
			arr[0] = ft_substr(str, 0, i + 1);
			arr[1] = ft_substr(str, i + 1, ft_strlen(str));
		}
		i++;
	}
	return (arr);
}

char	*export_get_value(char *key)
{
	t_bd_lst	*found;
	char		*res;
	char		**arr;

	res = NULL;
	found = bd_lstfind(get_local_env(), key, ft_strlen(key), ft_strncmp);
	if (found)
	{
		arr = key_val_split(found->content, '=');
		res = bd_strdup(arr[1]);
		free_array(arr);
	}
	return (res);
}

int		export_add_cmd(t_cmd *cmd)
{

}

int		export_add(t_prm *prm, t_cmd *cmd)
{
	char **arr;
	int i;

	i = 0;
	while (cmd->args[i])
	{
		arr = key_val_split(cmd->args[i], '=');
		if (arr[1])
		{
			
		}

		//if i have key value in the list then i need to replace it with another val
		
		free_array(arr);
		i++;
	}
	// if argument array store more than one argument need to add them all.
	// split argument array into l-part and r-part
	// check if r-part is exist
	// if it is not then a new value wont be added into env list
	// if it is then need to add value into both lists

	//add:
	// first need to check if there is a value stored in current list
	// if it is then new value will overwrite an old value.
	// if it is not then need to create a new node of the list
	// then insert element using push_sort function for sorted list(export list) and
	// addback for unsorted list (env list)
	return (0);
}

int		export_print(t_prm *prm)
{
	t_bd_lst *lst_copy;
	
	lst_copy = bd_lstcopy(prm->env_list, def_cont_copy);
	bd_lstsort_merge(&(lst_copy), bd_strcmp);
	bd_lstiter(lst_copy, print_export_node);
	bd_lstclear(&lst_copy, free);
	return (0);
}

int		cmd_export(t_cmd *cmd)
{
	t_prm *prm;
	
	prm = get_parameters(0);
	if (sizeof_array(cmd->args) == 0)
	{
		prm->exit_code = export_print(prm);
	}
	else
	{
		prm->exit_code = export_add(prm, cmd);
	}
	return (0);
}