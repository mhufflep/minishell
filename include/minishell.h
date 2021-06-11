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

# include "egg.h"
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
# define DQOUTE '"'
# define SLASH '\\'

# define ENV_SEP "="

# define TRUNC 1
# define APPEND 2

typedef struct termios t_term;

typedef enum e_stream
{
	INVALID = -2,
	UNDEFINED = -1,
	IN = 0,
	OUT = 1
	// ERR = 2
}			t_stream;

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

typedef struct	s_redir
{
	t_stream	s_id;
	int			flag;
	int			rights;
	char		*filename;
}				t_redir;

typedef struct  s_cmd
{
	int			is_child;
	pid_t		pid;
	int			rdir[2];		// change name
	int			pipe[2];
	char		**args;				//аргументы (и опции) команды
    int			is_pipe;			//стоит ли после команды pipe
    int			r_flag;				//стоит ли после команды redir, если значение 2 - значит двойной
	int			rr_flag;
	t_blst		*out;
	t_blst		*in;
	// t_blst	*err;
}               t_cmd;

typedef struct	s_sh
{
	int	io[3];
	char **env;
	char **argv;
	int argc;
	int curs_pos;
	int	line_len;
	int	exit_code;
	int enable;
	char *line;
	char input[5];

	t_caps	caps;
	t_term	*term;
	t_term	*def_term;

	t_blst	*history;
	t_blst	*hptr;
	t_blst	*env_list;
	t_blst	*cmds_ptr;
	t_blst	**cmds; 			//массив листов команд, в поле data каждой будет лежать t_cmd *
}					t_sh;

void		reader(t_sh *);
int			lexer(char *str);
int			parser(t_sh *);
void		executor(t_sh *);
int			expander(t_sh *);


/* MAIN FUNCTIONS */
t_sh		*setup_settings(int, char **, char **);
void		reset_parameters(t_sh *);

/* HISTORY */
void		history_read(t_sh *sh);
void		history_add(t_sh *sh);
void		history_save(t_sh *sh);
void		history_if_prev(t_sh *sh);

/* BUILTIN */
int			cmd_21school(t_sh *sh, t_cmd *cmd);

int			redirects(t_cmd *cmd);

int			cmd_cd(t_cmd *cmd);
int			cmd_pwd(t_cmd *cmd);
int			cmd_env(t_cmd *cmd);
int			cmd_exit(t_sh *sh, t_cmd *cmd);
int			cmd_echo(t_cmd *cmd);
int			cmd_clear(t_sh *sh, t_cmd *cmd);
int			cmd_unset(t_sh *sh, t_cmd *cmd);
int			cmd_learnc(t_cmd *cmd);
int			cmd_export(t_sh *sh, t_cmd *cmd);
int			cmd_usercmd(t_sh *sh, t_cmd *cmd);
int			cmd_history(t_sh *sh, t_cmd *cmd);
int			cmd_not_found(t_cmd *cmd);

/* TERMINAL */
void		change_term_settings(t_term *term);
int			setup_terminal(t_sh *sh);
t_term		*create_term_struct(void);

/* KEYS */
int			is_printable_sym(unsigned int input);
int			is_printable(char *input);
void		key_up_action(t_sh *sh);
void		key_down_action(t_sh *sh);
void		key_left_action(t_sh *sh);
void		key_right_action(t_sh *sh);
void		key_tab_action(void);
void		key_ctrl_l_action(t_sh *sh);
void		key_ctrl_d_action(t_sh *sh);
void		key_bspace_action(t_sh *sh);
void		key_other_action(t_sh *sh);
void		key_home_action(t_sh *sh);
void		key_end_action(t_sh *sh);
void		clear_prompt(t_sh *sh);



/* ARRAY */
int			sizeof_array(char **arr);
char		**array_copy(char **proto, char *(*copy_func)(const char *));
void		*free_array(char **array);
void 		print_array(char **arr);
void		iter_array(char **arr, void (*func)(char *));


//MOVE TO SPECIFIC AREAS
char		*insert_into2(char **src, char *add, int index, void (*free_ctl)(void *));
char		*insert_into(char *src, char *add, int index, void (*free_ctl)(void *));
char 		*remove_from(char *src, int index);
char		*replace_by(char **src, int index, int len, char *add, void (*free_ctl)(void *));
void		recognize_symbol(t_sh *sh);
void		print_export_node(void *data);
char 		*asterisk(char *pattern);
int			is_option(char *opt, char *valid_opt);
void 		clrscr(t_sh *sh);

/* INIT */
t_sh		*setup_settings(int argc, char **argv, char **env);
int			setup_env_lists(t_sh	*sh);
int			setup_parameters(t_sh **sh);
int			setup_terminal(t_sh	*sh);
void		reset_settings(t_sh	*sh);
char		**key_val_split(char *str, char *sep);

/* GETTERS */
t_sh		*get_sh(t_sh *sh);
t_blst	*env_llist(void);


/* PARSER */

int			parse_redirect(t_cmd *cmd, char **str);
void		parse_dollar(char **s, int code);
void		parse_tilda(char **s);
int			is_slash(char *s, int i);
// int			escape_pair(char **str);
int			escape_symbols(char **arr_str);
char		**shell_split(char *s, char separator);
int			skip_in_quote(char **s, int i, char quote_mark);
size_t		read_str(char **s, int i, char separator, int is_escaped);
void		cmds_arr_create(t_sh *sh, int size);
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
int			export_add(t_sh *sh, t_env *env);


/* SIGNAL */
void		int_handler(int num);
void		quit_handler(int num);

/* DIR_UTILS */
int			is_dir(char *directory);
int			is_in_dir(char *name, char *directory);

int 		redirect(t_blst *io);//, t_stream sid);

int			shell_exit(t_sh *sh);

void	set_tcap_sh(t_sh *sh);

void	restore_tcap_sh(t_sh *sh);
#endif
