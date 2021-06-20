#include "msh.h"

int		cmd_learnc(t_cmd *cmd)
{
	(void)cmd;
	char str[139] = "јѾѱѶ҉ҍ!҄ѻѱѸѱ҃ѶѼѹ!ご!ѸѾѱѶ҉ҍ!Ѣљ-!ўѶ!ѸѾѱѶ҉ҍ!҄ѻѱѸѱ҃ѶѼѹ!.!Ѿ҄-!҆҄Ѻ!҂ѿ҂ѹ/";
	int i;

	i = 0;
	while (i < 138)
	{
		str[i] -= 1;
		i++;
	}
	write(1, "\033[5;3m", 7);
	write(1, str, 116);
	write(1, "\033[0m", 5);
	write(1, "\n", 1);
	return (0);
}
