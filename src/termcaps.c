#include "msh.h"

char	*init_tcap(t_sh *sh, char *key)
{
	char	*res;

	res = tgetstr(key, 0);
	if (res == NULL)
	{
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd(" tcap failed\n", STDERR_FILENO);
		shell_exit(sh);
	}
	return (res);
}

void	setup_caps(t_sh *sh)
{
	sh->caps.rc = init_tcap(sh, "rc");
	sh->caps.sc = init_tcap(sh, "sc");
	sh->caps.cd = init_tcap(sh, "cd");
	sh->caps.dc = init_tcap(sh, "dc");
	sh->caps.le = init_tcap(sh, "le");
	sh->caps.nd = init_tcap(sh, "nd");
	sh->caps.im = init_tcap(sh, "im");
	sh->caps.ei = init_tcap(sh, "ei");
	sh->caps.cl = init_tcap(sh, "cl");
}

void	set_tcap_sh(t_sh *sh)
{
	sh->term->c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, sh->term);
}

void	restore_tcap_sh(t_sh *sh)
{
	sh->term->c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, sh->term);
}
