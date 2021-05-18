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
# include <sys/wait.h>

# include "libft.h"
# include "shell_keys.h"
# include "get_next_line.h"
# include "builtin.h"
# include "bidirectional_list.h"

// 0, 255, 197
# define SHELL_PROMPT "\e[38;2;247;219;1672me-bash # \e[0m"
# define HISTORY_FILENAME ".e-bash_history"
# define HISTORY_FILEPATH "./"

typedef struct termios t_term;

typedef struct  s_cmd
{
	char *cmd;				//текущая команда
	char *options;			//опции команды
	char **args;			//аргументы команды
    int is_pipe : 1;		//стоит ли после команды pipe
    int is_redirect : 1;	//стоит ли после команды redir
}               t_cmd;

typedef struct  s_prm
{
	char **env;
	char **argv;
	int argc;
	int cursor_pos;
	int	line_len;
	int	exit_code;
	int status;
	char *line;
	char input[5];

	t_term	*term;
	t_term	*def_term;

	t_bd_lst	*history;
	t_bd_lst	*history_ptr;
	t_bd_lst	*unsorted_env;
	t_bd_lst	*sorted_env;
	t_bd_lst	*cmds_ptr;
	t_bd_lst	**cmds; //массив листов команд, в поле content каждой будет лежать t_cmd *
}               t_prm;


/* MAIN FUNCTIONS */
t_prm	*setup_settings(int, char **, char **);
void	read_line(t_prm *);
void	parse_line(t_prm *);
void	execute_line(t_prm *);
void	reset_parameters(t_prm *);

/* HISTORY */
int		read_history(t_prm *prm);
int		history_add(t_bd_lst *node);
int		history_next(t_prm *prm);
int		history_prev(t_prm *prm);
int		save_history(t_bd_lst *node);


/* BUILTIN */
void		cmd_cd(t_prm *prm);
void		cmd_pwd(t_prm *prm);
void		cmd_env(t_prm *prm);
void		cmd_echo(t_prm *prm);
void		cmd_unset(t_prm *prm);
void		cmd_learnc(t_prm *prm);
void		cmd_export(t_prm *prm);
void		cmd_history(t_prm *prm);
void		cmd_not_found(t_prm *prm);


int			execute(char buff[], t_prm *prm);


/* TERMINAL */
void		change_term_settings(t_term *term);
int			setup_terminal(t_prm	*prm);
t_term		*create_term_struct(void);


/* KEYS */
int			is_printable_sym(unsigned int input);
int			is_printable(char *input);
int			is_spec_key(char *input);
void		key_up_action(t_prm *prm);
void		key_down_action(t_prm *prm);
void		key_left_action(t_prm *prm);
void		key_right_action(t_prm *prm);
void		key_ctrl_l_action(t_prm *prm);
void		key_bspace_action(t_prm *prm);
void		key_other_action(t_prm *prm);
void		clear_prompt(void);



char *remove_from(char *src, int index, void (*free_ctl)(void *));
char *insert_into(char *src, int index, char symbol, void (*free_ctl)(void *));

/* INITIALIZATION */
t_prm		*setup_settings(int argc, char **argv, char **env);
int			setup_env_lists(t_prm	*prm);
int			setup_parameters(t_prm **prm);
int			setup_terminal(t_prm	*prm);
void		reset_settings(t_prm	*prm);

t_prm		*get_parameters(t_prm *prm);

/* ERROR */
void throw_error(void); // ???

#endif
