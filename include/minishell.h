#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"

#include <term.h>
#include <termios.h>

#include "bidirectional_list.h"

typedef struct  s_prm
{
    char **env;
    char **argv;
    int argc;

    t_bd_lst *unsorted_env;
    t_bd_lst *sorted_env;
    t_bd_lst **cmds;
}               t_prm;


int    set_default(void *prm, int size);

#endif