#include "minishell.h"

void	print_export_node(void *content)
{
	if (content != NULL)
	{
		printf("declare -x %s\n", (char *)content);
	}
}

int export_add(t_cmd *cmd)
{
	//if argument array store more than one argument need to add them all.
	//split argument array into l-part and r-part
	//check if r-part is exist
	//if it is not then a new value wont be added into env list
	//if it is then need to add value into both lists

	//add:
	//first need to check if there is a value stored in current list
	// if it is then new value will overwrite an old value.
	// if it is not then need to create a new node of the list
	// then insert element using push_sort function for sorted list(export list) and
	// addback for unsorted list (env list)
	(void)cmd;
	return (0);
}

//int export_cmd(t_cmd *cmd)
//{
//	if (arr_count(cmd->args) == 0)
//		export_add(cmd);
//	else
//		export_show(cmd); //cmd_export
//	return (0);
//}

int cmd_export(t_cmd *cmd)
{
	//check commands
	(void)cmd;
	t_prm *prm = get_parameters(NULL);
	bd_lstiter(prm->sorted_env, print_export_node);
	return (0);
}