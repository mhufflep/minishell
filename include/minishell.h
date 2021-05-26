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
# define SHELL_NAME "e-bash"
# define SHELL_PROMPT "\e[38;2;247;219;1672me-bash # \e[0m"
# define HISTORY_FILENAME ".e-bash_history"
# define HISTORY_FILEPATH "./"
# define QUOTE '\''
# define D_QUOTE '"'
# define SLASH '\\'

# define ENV_SEP "="

typedef struct termios t_term;

typedef struct	s_env
{
	char	*key;
	char	*sep;
	char	*val;
}				t_env;

typedef struct  s_cmd
{
	char *cmd;				//текущая команда
	char *options;			//опции команды
	char **args;			//аргументы команды
    int is_pipe : 1;		//стоит ли после команды pipe
    int is_redirect : 1;	//стоит ли после команды redir
	int fd;
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
	t_bd_lst	*env_list;
	t_bd_lst	*cmds_ptr;
	t_bd_lst	**cmds; //массив листов команд, в поле content каждой будет лежать t_cmd *
}               t_prm;


/* MAIN FUNCTIONS */
t_prm		*setup_settings(int, char **, char **);
void		read_line(t_prm *);
void		execute_line(t_prm *);
void		reset_parameters(t_prm *);

/* HISTORY */
int			read_history(t_prm *prm);
int			history_add(t_bd_lst *node);
int			history_next(t_prm *prm);
int			history_prev(t_prm *prm);
int			save_history(t_bd_lst *node);


/* BUILTIN */
int			cmd_cd(t_prm *prm, t_cmd *cmd);
int			cmd_pwd(t_cmd *cmd);
int			cmd_env(t_prm *prm, t_cmd *cmd);
int			cmd_exit(t_cmd *cmd);
int			cmd_echo(t_cmd *cmd);
int			cmd_unset(t_prm *prm, t_cmd *cmd);
int			cmd_learnc(t_cmd *cmd);
int			cmd_export(t_prm *prm, t_cmd *cmd);
int			cmd_usercmd(t_cmd *cmd);
int			cmd_history(t_prm *prm, t_cmd *cmd);
int			cmd_not_found(t_cmd *cmd);

/* TERMINAL */
void		change_term_settings(t_term *term);
int			setup_terminal(t_prm	*prm);
t_term		*create_term_struct(void);

/* KEYS */
int			is_printable_sym(unsigned int input);
int			is_printable(char *input);
void		key_up_action(t_prm *prm);
void		key_down_action(t_prm *prm);
void		key_left_action(t_prm *prm);
void		key_right_action(t_prm *prm);
void		key_tab_action(void);
void		key_ctrl_l_action(t_prm *prm);
void		key_bspace_action(t_prm *prm);
void		key_other_action(t_prm *prm);
void		clear_prompt(void);

//MOVE TO SPECIFIC AREAs
char		*insert_into(char *src, char *add, int index, void (*free_ctl)(void *));
char		*remove_from(char *src, int index, void (*free_ctl)(void *));
int			sizeof_array(char **arr);
void		*free_array(char **array);
void 		print_array(char **arr);
void		iter_array(char **arr, void (*func)(char *));
void		recognize_symbol(t_prm *prm);
void	print_export_node(void *content);


/* INITIALIZATION */
t_prm		*setup_settings(int argc, char **argv, char **env);
int			setup_env_lists(t_prm	*prm);
int			setup_parameters(t_prm **prm);
int			setup_terminal(t_prm	*prm);
void		reset_settings(t_prm	*prm);
char		**key_val_split(char *str, char *sep);

/* GETTERS */
t_prm		*get_prm(t_prm *prm);
t_bd_lst	*env_llist(void);


/* PARSER */
int			parse_line(t_prm *prm);
char		**shell_split(char *s, const char *separators);
void		cmds_arr_create(t_prm *prm, int size);
t_cmd		*command_create(char *cmd, char **args);

/* ERROR */
void		throw_error(char *msg);
void 		print_error(char *msg);
void		cmd_error(char *cmd, char *arg, char *msg);

/* ENV_UTILS */
void		env_del(void *node);
void		*env_copy(void *node);
void		*env_parse(void *str);
t_env		*env_create(char *key, char *sep, char *val);
int			env_cmp(void *data1, void *data2, size_t n);
t_env		*env_get_local(char *key);
char		*env_get_val(char *key);
int			env_valid(t_env *env);

#endif
