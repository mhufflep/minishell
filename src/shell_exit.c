#include "minishell.h"

int shell_exit(t_sh *sh)
{
    // close(sh->io[0]);
    // close(sh->io[1]);
    tcsetattr(0, TCSANOW, sh->def_term);
    exit(sh->exit_code);
}