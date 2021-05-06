#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <errno.h>

# include "libft.h"
# include "shell_keys.h"
# include "get_next_line.h"
# include "bidirectional_list.h"
// 0, 255, 197
# define SHELL_PROMPT "\e[38;2;247;219;1672me-bash # \e[0m"
# define HISTORY_FILENAME ".e-bash_history"
# define HISTORY_FILEPATH "./"

typedef struct termios t_term;

typedef struct  s_cmd
{
	char *cmd;			//текущая команда
	char *options;		//опции команды
	char *args;			//аргументы команды
    int is_pipe;		//стоит ли после команды pipe
    int is_redirect;	//стоит ли после команды redir
}               t_cmd;

typedef struct  s_prm
{
	char **env;
	char **argv;
	int argc;
	int cursor_pos;

	t_term	*term;
	t_term	*def_term;

	t_bd_lst	*history;
	t_bd_lst	*history_ptr;
	t_bd_lst	*unsorted_env;
	t_bd_lst	*sorted_env;
	t_bd_lst	*cmds_ptr;
	t_bd_lst	*cmds; //лист команд, в поле content каждой будет лежать t_cmd *
}               t_prm;

/* SET ANY STRUCT TO ZERO */
void	set_default(void *prm, int size);

/* HISTORY */
int		read_history(t_bd_lst **history);
int		save_history(t_bd_lst **history);


/* COMMANDS */
void	cmd_pwd(void);
void	cmd_env(t_prm *prm);
void	cmd_unset(t_prm *prm);
void	cmd_export(t_prm *prm);
void	cmd_history(t_prm *prm);
void	cmd_not_found(t_prm *prm);

int		execute(char buff[], t_prm *prm);


/* TERMINAL */
void	change_term_settings(t_term *term);
int		init_term_struct(t_prm	*prm);
t_term	*create_term_struct(void);

/* KEYS */
void	key_up_action(t_prm *prm);
void	key_down_action(t_prm *prm);
void	key_left_action(t_prm *prm);
void	key_right_action(t_prm *prm);

void	clear_prompt(void);

/* INITIALIZATION */
int		init_resources(t_prm **prm, int argc, char **argv, char **env);
int		init_env_lists(t_prm *prm);
int		init_prm_struct(t_prm **prm);
int		init_term_struct(t_prm	*prm);
#endif