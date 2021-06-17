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

# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>

# include "egg.h"
# include "libft.h"
# include "builtin.h"
# include "shell_keys.h"
# include "get_next_line.h"
# include "error_messages.h"
# include "bidirectional_list.h"

# define SHELL_NAME "e-bash"
# define SHELL_PROMPT "\e[38;2;247;219;1672me-bash # \e[0m"
# define HISTORY_FILENAME ".e-bash_history"

# define QUOTE '\''
# define DQOUTE '"'
# define SLASH '\\'

# define ENV_SEP "="

typedef enum e_stream
{
	UNDEFINED	= -2,
	INVALID		= -1,
	IN			= 0,
	OUT			= 1
}			t_stream;

typedef struct s_caps
{
	char		*rc;
	char		*cd;
	char		*le;
	char		*dc;
	char		*nd;
	char		*sc;
	char		*im;
	char		*dm;
	char		*ei;
	char		*ed;
	char		*am;
	char		*cl;
}				t_caps;

typedef struct s_env
{
	char		*key;
	char		*sep;
	char		*val;
}				t_env;

typedef struct s_redir
{
	t_stream	s_id;
	int			flag;
	int			rights;
	char		*filename;
}				t_redir;

typedef struct s_cmd
{
	pid_t		pid;
	int			rdir[2];
	int			pipe[2];
	int			is_child;
	char		**args;				
	int			is_pipe;			
	int			r_flag;
	int			rr_flag;
	t_blst		*out;
	t_blst		*in;
}				t_cmd;

typedef struct s_sh
{
	char			*name;
	int				enable;
	int				ch_pid;
	int				exit_code;
	int				sig_code;

	int				argc;
	char			**env;
	char			**argv;

	char			input[5];
	int				curs_pos;
	int				line_len;

	int				io[3];
	int				have_pipes;
	int				have_redir;
	int				have_rredir;

	t_caps			caps;
	struct termios	*term;
	struct termios	*def_term;

	t_blst			*hptr;
	t_blst			*history;
	t_blst			*env_list;
	t_blst			*cmds_ptr;
	t_blst			**cmds;
}					t_sh;

/* 
** MAIN FUNCTIONS
*/
void			reader(t_sh *sh);
int				lexer(char *str);
int				parser(t_sh *sh);
void			executor(t_sh *sh);
int				expander(t_sh *sh);
int				shell_exit(t_sh *sh);

/*
** INIT
*/
t_sh			*get_sh(t_sh *sh);
void			reset_settings(t_sh	*sh);
void			set_tcap_sh(t_sh *sh);
void			setup_caps(t_sh *sh);
void			restore_tcap_sh(t_sh *sh);
int				setup_env_lists(t_sh *sh);
int				setup_parameters(t_sh **sh);
char			*init_tcap(t_sh *sh, char *key);
char			**key_val_split(char *str, char *sep);
t_sh			*setup_settings(int argc, char **argv, char **env);
void			update_shlvl(t_sh *sh);
void			update_path(void);

/*
** HISTORY
*/
void			history_read(t_sh *sh);
void			history_add(t_sh *sh);
void			history_save(t_sh *sh);
void			history_if_prev(t_sh *sh);

/*
** BUILTIN
*/
int				cmd_cd(t_cmd *cmd);
int				cmd_pwd(t_cmd *cmd);
int				cmd_env(t_cmd *cmd);
int				cmd_exit(t_sh *sh, t_cmd *cmd);
int				cmd_echo(t_cmd *cmd);
int				cmd_clear(t_sh *sh, t_cmd *cmd);
int				cmd_unset(t_sh *sh, t_cmd *cmd);
int				cmd_learnc(t_cmd *cmd);
int				cmd_export(t_sh *sh, t_cmd *cmd);
int				cmd_usercmd(t_sh *sh, t_cmd *cmd);
int				cmd_history(t_sh *sh, t_cmd *cmd);
int				cmd_not_found(t_cmd *cmd);

/*
** CMD_UTILS
*/
t_cmd			*cmd_alloc(void);
int				cmd_add_node(t_sh *sh, t_cmd *cmd, int i);

/*
** BUILTIN'S UTILS
*/
int				is_option(char *opt, char *valid_opt);

/*
** TERMINAL
*/
int				setup_terminal(t_sh *sh);
struct termios	*create_term_struct(void);

/*
** KEYS
*/
void			key_up_action(t_sh *sh);
void			key_down_action(t_sh *sh);
void			key_left_action(t_sh *sh);
void			key_right_action(t_sh *sh);
void			key_tab_action(void);
void			key_ctrl_l_action(t_sh *sh);
void			key_ctrl_d_action(t_sh *sh);
void			key_bspace_action(t_sh *sh);
void			key_ctrl_c_action(t_sh *sh);
void			key_other_action(t_sh *sh);
void			key_home_action(t_sh *sh);
void			key_end_action(t_sh *sh);
void			recognize_symbol(t_sh *sh);

/*
** KEY UITLS
*/
int				is_printable(char *str);
int				is_ascii(char *str);
void			cursor_save(void);
void			cursor_restore(void);
void			update_curs_pos(t_sh *sh);
int				ends_with(char *str, char *end);
/* 
** ARRAY
*/
void			print_array(char **arr);
int				sizeof_array(char **arr);
void			*free_array(char **arr);
void			iter_array(char **arr, void (*func)(char *));
char			**array_copy(char **proto, char *(*copy)(const char *));

/*
** CLEAN
*/
void			clean_prompt(t_sh *sh);
void			clean_screen(t_sh *sh);

/*
** STRING MODIFIERS
*/
char			*insert(char **s, char *add, int i, void (*del)(void *));
char			*insert_into(char *src, char *add, int i, void (*del)(void *));
char			*remove_from(char *src, int i);
char			*replace_by(char **src, int i, int len, char *add);

/*
** REDIRECTS & PIPES
*/
void			child_pipes(t_sh *sh, t_blst *lst, t_cmd *cmd);
void			parent_pipes(t_sh *sh, t_cmd *cmd);
void			waitproc(t_cmd *cmd);
void			spawn_pipes(t_sh *sh, t_blst *lst);
int				redirect(t_blst *io);
void			free_redir(void *data);
int				execute_cmd(t_sh *sh, t_cmd *cmd);
void			execute_pipeline(t_sh *sh, t_blst *lst);
void			restore_fds(t_sh *sh);
void			close_fds(t_cmd *cmd);

/* 
** PARSER
*/
t_redir			*redir_alloc(void);
int				parse_redirect(t_cmd *cmd, char **str);
void			parse_dollar(char **s, int code);
void			parse_tilda(char **s);
int				is_slash(char *s, int i);
void			skip_spaces(char *str, int *i);
int				amount_spaces(char *str);
int				escape_symbols(char **arr_str);
char			**shell_split(char *s, char sep);
int				skip_in_quote(char **s, int i, char quote_mark);
size_t			read_str(char **s, int i, char separator, int is_escaped);
void			cmds_arr_create(t_sh *sh, int size);
t_cmd			*command_create(char **args);
int				spliting_last_node(t_sh *sh, char **cmds, char **pipes, int i);
void			skip_spaces(char *str, int *i);
/* 
** ERROR
*/
void			throw_error(char *msg, int code_status);
void			print_error(char *msg, int code_status);
void			cmd_error(char *cmd, char *arg, char *msg);

/*
** ENV_UTILS
*/
t_blst			*env_llist(void);
t_env			*env_create(char *key, char *sep, char *val);
int				env_update(t_env *old, t_env *new);
int				env_add(t_sh *sh, t_env *env);
int				env_valid(t_env *env);
void			env_del(void *node);
int				env_cmp(void *d1, void *d2, size_t n);
void			*env_dup(void *node);
void			*copy_to_env(void *str);
void			*copy_from_env(void *node);

char			*env_get_val(char *key);
t_env			*env_get_local(char *key);

/*
** SIGNAL 
*/
void			signals_off(void);
void			signals_on(void);
void			int_handler(int num);
void			quit_handler(int num);

/*
** DIR_UTILS
*/
int				is_dir(char *directory);
int				is_in_dir(char *name, char *directory);

/*
** ASTERISK
*/
char *asterisk(char *pattern);

#endif
