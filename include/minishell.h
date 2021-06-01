#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <term.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>


# include "libft.h"
# include "builtin.h"
# include "shell_keys.h"
# include "get_next_line.h"
# include "error_messages.h"
# include "bidirectional_list.h"

// 0, 255, 197
# define SHELL_NAME "e-bash"
# define SHELL_PROMPT "\e[38;2;247;219;1672me-bash # \e[0m"
# define HISTORY_FILENAME ".e-bash_history"
# define QUOTE '\''
# define D_QUOTE '"'
# define SLASH '\\'

# define ENV_SEP "="

# define TRUNC 1
# define APPEND 2

typedef struct termios t_term;

typedef struct	s_caps
{
	char *rc;
	char *cd;
	char *le;
	char *dc;
	char *nd;
	char *sc;

	char *im;
	char *dm;
	char *ei;
	char *ed;
	char *am;
	char *cl;
}				t_caps;

typedef struct	s_env
{
	char	*key;
	char	*sep;
	char	*val;
}				t_env;

typedef struct  s_cmd
{
	char		**args;				//аргументы (и опции) команды
    int			is_pipe;			//стоит ли после команды pipe
    int			is_redirect;		//стоит ли после команды redir, если значение 2 - значит двойной
	t_bd_lst	*filenames;
}               t_cmd;

typedef struct  s_prm
{
	char **env;
	char **argv;
	int argc;
	int curs_pos;
	int	line_len;
	int	exit_code;
	int enable;
	char *line;
	char input[5];


	// char *rc;
	// char *cd;
	// char *le;
	// char *dc;
	// char *nd;
	// char *sc;

	// char *im;
	// char *dm;
	// char *ei;
	// char *ed;
	// char *am;

	t_caps	caps; //remove?

	t_term	*term;
	t_term	*def_term;

	t_bd_lst	*history;
	t_bd_lst	*hptr;
	t_bd_lst	*env_list;
	t_bd_lst	*cmds_ptr;
	t_bd_lst	**cmds; //массив листов команд, в поле data каждой будет лежать t_cmd *
}               t_prm;

void		reader(t_prm *);
int			lexer(char *str);
int			parser(t_prm *);
void		executor(t_prm *);
int			expander(t_prm *);


/* MAIN FUNCTIONS */
t_prm		*setup_settings(int, char **, char **);
void		reset_parameters(t_prm *);

/* HISTORY */
void		history_read(t_prm *prm);
void		history_add(t_prm *prm);
void		history_save(t_prm *prm);

/* BUILTIN */
int			cmd_cd(t_cmd *cmd);
int			cmd_pwd(t_cmd *cmd);
int			cmd_env(t_cmd *cmd);
int			cmd_exit(t_prm *prm, t_cmd *cmd);
int			cmd_echo(t_cmd *cmd);
int			cmd_clear(t_prm *prm, t_cmd *cmd);
int			cmd_unset(t_prm *prm, t_cmd *cmd);
int			cmd_learnc(t_cmd *cmd);
int			cmd_export(t_prm *prm, t_cmd *cmd);
int			cmd_usercmd(t_cmd *cmd);
int			cmd_history(t_prm *prm, t_cmd *cmd);
int			cmd_not_found(t_cmd *cmd);

/* TERMINAL */
void		change_term_settings(t_term *term);
int			setup_terminal(t_prm *prm);
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
void		key_ctrl_d_action(t_prm *prm);
void		key_bspace_action(t_prm *prm);
void		key_other_action(t_prm *prm);
void		key_home_action(t_prm *prm);
void		key_end_action(t_prm *prm);
void		clear_prompt(t_prm *prm);



/* ARRAY */
int			sizeof_array(char **arr);
char		**array_copy(char **proto, char *(*copy_func)(const char *));
void		*free_array(char **array);
void 		print_array(char **arr);
void		iter_array(char **arr, void (*func)(char *));


//MOVE TO SPECIFIC AREAS
char		*insert_into2(char **src, char *add, int index, void (*free_ctl)(void *));
char		*insert_into(char *src, char *add, int index, void (*free_ctl)(void *));
char		*remove_from(char *src, int index, void (*free_ctl)(void *));
char		*replace_by(char **src, int index, int len, char *add, void (*free_ctl)(void *));
void		recognize_symbol(t_prm *prm);
void		print_export_node(void *data);
char 		*asterisk(char *pattern);
int			is_option(char *opt, char *valid_opt);
void 		clrscr(t_prm *prm);

/* INIT */
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

int			is_slash(char *s, int i);
int			escape_pair(char **str);
int			escape_all(char **str);
char		**cmd_split(char *s, char separator);
size_t		read_str(char **s, int i, char separator, int is_escaped);
int			check_quote(char **s, int i, char quote_mark, char separator);
void		cmds_arr_create(t_prm *prm, int size);
t_cmd		*command_create(char **args);

/* ERROR */
void		throw_error(char *msg, int code_status);
void 		print_error(char *msg, int code_status);
void		cmd_error(char *cmd, char *arg, char *msg);

/* ENV_UTILS */
void		env_del(void *node);
void		*env_dup(void *node);
char		*env_get_val(char *key);
t_env		*env_get_local(char *key);
t_env		*env_create(char *key, char *sep, char *val);
int			env_cmp(void *data1, void *data2, size_t n);
int			env_valid(t_env *env);

void		*copy_to_env(void *str);
void		*copy_from_env(void *node);

int			export_update(t_env *found, t_env *replacer);
int			export_add(t_prm *prm, t_env *env);


/* SIGNAL */
void		handler_int(int num);
void		handler_quit(int num);

/* DIR_UTILS */
int			is_dir(char *directory);
int			is_in_dir(char *name, char *directory);




#endif
