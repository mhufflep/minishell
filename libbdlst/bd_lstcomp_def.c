#include "bidirectional_list.h"

int			def_cont_comp(void *data1, void *data2)
{
	if (data1 && !data2)
		return (1);
	else if (!data2 && data2)
		return (-1);
	else if (!data1 && !data2)
		return (0);
	return (bd_strcmp((char *)data1, (char *)data2));
}